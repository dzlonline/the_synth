/*
 * theSynth – 4-voice wavetable engine for AVR Arduinos
 * Copyright (c) 2014-2025 Dzl / Illutron
 * Licensed under the MIT License; see the LICENSE file for details.
 */

#include "synth.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#include "tables.h"

namespace {
constexpr uint8_t kVoices = synth::kVoiceCount;

volatile uint16_t gPhase[kVoices];
volatile uint16_t gFrequencyTuning[kVoices];
volatile uint8_t gAmplitude[kVoices];
volatile uint16_t gPitch[kVoices];
volatile int16_t gMod[kVoices];
const uint8_t* volatile gWaveTables[kVoices];
const uint8_t* volatile gEnvelopeTables[kVoices];
volatile uint16_t gEnvelopePhase[kVoices];
volatile uint16_t gEnvelopeSpeed[kVoices];
volatile uint8_t gDivider = 0;
volatile bool gTickFlag = false;
volatile uint8_t gCurrentMode = CHA;

inline void clearState() {
  for (uint8_t i = 0; i < kVoices; ++i) {
    gPhase[i] = 0;
    gFrequencyTuning[i] = 0;
    gAmplitude[i] = 0;
    gPitch[i] = pgm_read_word(&PITCHS[0]);
    gMod[i] = 0;
    gWaveTables[i] = reinterpret_cast<const uint8_t*>(SinTable);
    gEnvelopeTables[i] = reinterpret_cast<const uint8_t*>(Env0);
    gEnvelopePhase[i] = 0x8000;
    gEnvelopeSpeed[i] = pgm_read_word(&EFTWS[0]);
  }
  gDivider = 0;
  gTickFlag = false;
}

inline void clampToPwmRange(int16_t& value) {
  if (value < -127) {
    value = -127;
  } else if (value > 127) {
    value = 127;
  }
}

inline void refreshFrequency(uint8_t voice) {
  if (voice >= kVoices) {
    return;
  }
  const uint16_t base = gPitch[voice];
  const int16_t mod = gMod[voice];
  const uint16_t envPhase = gEnvelopePhase[voice];
  int32_t modulator = 0;
  if (mod != 0) {
    modulator = ((static_cast<int32_t>(base >> 6) * static_cast<int32_t>(envPhase >> 6)) / 128) * mod;
  }
  int32_t result = static_cast<int32_t>(base) + modulator;
  if (result < 0) {
    result = 0;
  } else if (result > 0xFFFF) {
    result = 0xFFFF;
  }
  gFrequencyTuning[voice] = static_cast<uint16_t>(result);
}

#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328PB__) || defined(__AVR_ATmega168__) || defined(__AVR_ATmega88__) || defined(__AVR_ATmega48__)
#define SYNTH_OC2A_DDR DDRB
#define SYNTH_OC2A_BIT DDB3
#define SYNTH_OC2B_DDR DDRD
#define SYNTH_OC2B_BIT DDD3
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
#define SYNTH_OC2A_DDR DDRB
#define SYNTH_OC2A_BIT DDB4
#define SYNTH_OC2B_DDR DDRH
#define SYNTH_OC2B_BIT DDH6
#elif defined(__AVR_ATmega644P__) || defined(__AVR_ATmega1284P__)
#define SYNTH_OC2A_DDR DDRD
#define SYNTH_OC2A_BIT DDD7
#define SYNTH_OC2B_DDR DDRD
#define SYNTH_OC2B_BIT DDD6
#else
#error "Unsupported AVR MCU: Timer2 pin mapping unknown"
#endif

inline void enableChannelA() {
  SYNTH_OC2A_DDR |= _BV(SYNTH_OC2A_BIT);
}

inline void enableChannelB() {
  SYNTH_OC2B_DDR |= _BV(SYNTH_OC2B_BIT);
}

}  // namespace

ISR(TIMER1_COMPA_vect) {
  gDivider = (gDivider + 1) & 0x03;
  if (gDivider == 0) {
    gTickFlag = true;
  }

  const uint8_t voice = gDivider;

  if ((gEnvelopePhase[voice] >> 8) & 0x80) {
    gAmplitude[voice] = 0;
  } else {
    gEnvelopePhase[voice] = static_cast<uint16_t>(gEnvelopePhase[voice] + gEnvelopeSpeed[voice]);
    const uint8_t envIndex = static_cast<uint8_t>(gEnvelopePhase[voice] >> 8);
    gAmplitude[voice] = pgm_read_byte(gEnvelopeTables[voice] + envIndex);
  }

  int16_t mix = 0;
  for (uint8_t i = 0; i < kVoices; ++i) {
    gPhase[i] = static_cast<uint16_t>(gPhase[i] + gFrequencyTuning[i]);
    const uint8_t phase = static_cast<uint8_t>(gPhase[i] >> 8);
    const int8_t sample = static_cast<int8_t>(pgm_read_byte(gWaveTables[i] + phase));
    mix += (sample * static_cast<int16_t>(gAmplitude[i])) >> 8;
  }

  mix >>= 2;
  clampToPwmRange(mix);
  int16_t output = 127 + mix;
  if (output < 0) {
    output = 0;
  } else if (output > 255) {
    output = 255;
  }
  OCR2A = static_cast<uint8_t>(output);
  OCR2B = static_cast<uint8_t>(output);

  refreshFrequency(voice);
}

bool synth::isValidVoice(uint8_t voice) {
  return voice < kVoiceCount;
}

void synth::configureTimer() {
  TCCR1A = 0;
  TCCR1B = _BV(WGM12) | _BV(CS10);
  TCCR1C = 0;
  const uint16_t compare = static_cast<uint16_t>((F_CPU / kSampleRate) + 0.5f);
  OCR1A = compare;
  TCNT1 = 0;
  TIMSK1 |= _BV(OCIE1A);
}

void synth::configureOutput(uint8_t mode) {
  switch (mode) {
    case DIFF:
      gCurrentMode = DIFF;
      TCCR2A = _BV(COM2A1) | _BV(COM2A0) | _BV(COM2B1) | _BV(COM2B0) | _BV(WGM21) | _BV(WGM20);
      enableChannelA();
      enableChannelB();
      break;
    case CHB:
      gCurrentMode = CHB;
      TCCR2A = _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
      enableChannelB();
      break;
    case CHA:
    default:
      gCurrentMode = CHA;
      TCCR2A = _BV(COM2A1) | _BV(WGM21) | _BV(WGM20);
      enableChannelA();
      break;
  }
  TCCR2B = _BV(CS20);
  OCR2A = 127;
  OCR2B = 127;
}

void synth::begin(uint8_t mode) {
  if (mode != DIFF && mode != CHB) {
    mode = CHA;
  }

  noInterrupts();
  clearState();
  configureTimer();
  configureOutput(mode);
  interrupts();
}

bool synth::synthTick() {
  if (gTickFlag) {
    gTickFlag = false;
    return true;
  }
  return false;
}

bool synth::voiceFree(uint8_t voice) const {
  if (!isValidVoice(voice)) {
    return true;
  }
  return ((gEnvelopePhase[voice] >> 8) & 0x80) != 0;
}

void synth::setupVoice(uint8_t voice, uint8_t wave, uint8_t pitch,
                       uint8_t env, uint8_t length, uint8_t mod) {
  setWave(voice, wave);
  setPitch(voice, pitch);
  setEnvelope(voice, env);
  setLength(voice, length);
  setMod(voice, mod);
}

void synth::setWave(uint8_t voice, uint8_t wave) {
  if (!isValidVoice(voice)) {
    return;
  }
  switch (wave) {
    case TRIANGLE:
      gWaveTables[voice] = reinterpret_cast<const uint8_t*>(TriangleTable);
      break;
    case SQUARE:
      gWaveTables[voice] = reinterpret_cast<const uint8_t*>(SquareTable);
      break;
    case SAW:
      gWaveTables[voice] = reinterpret_cast<const uint8_t*>(SawTable);
      break;
    case RAMP:
      gWaveTables[voice] = reinterpret_cast<const uint8_t*>(RampTable);
      break;
    case NOISE:
      gWaveTables[voice] = reinterpret_cast<const uint8_t*>(NoiseTable);
      break;
    case SINE:
    default:
      gWaveTables[voice] = reinterpret_cast<const uint8_t*>(SinTable);
      break;
  }
}

void synth::setPitch(uint8_t voice, uint8_t midiNote) {
  if (!isValidVoice(voice)) {
    return;
  }
  if (midiNote > 127) {
    midiNote = 127;
  }
  gPitch[voice] = pgm_read_word(&PITCHS[midiNote]);
  refreshFrequency(voice);
}

void synth::setEnvelope(uint8_t voice, uint8_t env) {
  if (!isValidVoice(voice)) {
    return;
  }
  switch (env) {
    case 2:
      gEnvelopeTables[voice] = reinterpret_cast<const uint8_t*>(Env1);
      break;
    case 3:
      gEnvelopeTables[voice] = reinterpret_cast<const uint8_t*>(Env2);
      break;
    case 4:
      gEnvelopeTables[voice] = reinterpret_cast<const uint8_t*>(Env3);
      break;
    case 0:
    case 1:
    default:
      gEnvelopeTables[voice] = reinterpret_cast<const uint8_t*>(Env0);
      break;
  }
}

void synth::setLength(uint8_t voice, uint8_t length) {
  if (!isValidVoice(voice)) {
    return;
  }
  if (length > 127) {
    length = 127;
  }
  gEnvelopeSpeed[voice] = pgm_read_word(&EFTWS[length]);
}

void synth::setMod(uint8_t voice, uint8_t mod) {
  if (!isValidVoice(voice)) {
    return;
  }
  gMod[voice] = static_cast<int16_t>(static_cast<int16_t>(mod) - 64);
  refreshFrequency(voice);
}

void synth::mTrigger(uint8_t voice, uint8_t midiNote) {
  if (!isValidVoice(voice)) {
    return;
  }
  setPitch(voice, midiNote);
  gEnvelopePhase[voice] = 0;
  refreshFrequency(voice);
}

void synth::setFrequency(uint8_t voice, float frequencyHz) {
  if (!isValidVoice(voice)) {
    return;
  }
  if (frequencyHz < 0.0f) {
    frequencyHz = 0.0f;
  }
  const float tuning = frequencyHz / (kSampleRate / 65535.0f);
  float clamped = tuning;
  if (clamped < 0.0f) {
    clamped = 0.0f;
  } else if (clamped > 65535.0f) {
    clamped = 65535.0f;
  }
  gPitch[voice] = static_cast<uint16_t>(clamped);
  refreshFrequency(voice);
}

void synth::setTime(uint8_t voice, float seconds) {
  if (!isValidVoice(voice) || seconds <= 0.0f) {
    return;
  }
  const float ftw = (1.0f / seconds) / (kSampleRate / (32767.5f * 10.0f));
  float clamped = ftw;
  if (clamped < 0.0f) {
    clamped = 0.0f;
  } else if (clamped > 65535.0f) {
    clamped = 65535.0f;
  }
  gEnvelopeSpeed[voice] = static_cast<uint16_t>(clamped);
}

void synth::trigger(uint8_t voice) {
  if (!isValidVoice(voice)) {
    return;
  }
  gEnvelopePhase[voice] = 0;
  gFrequencyTuning[voice] = gPitch[voice];
}

void synth::release(uint8_t voice) {
  if (!isValidVoice(voice)) {
    return;
  }
  gEnvelopePhase[voice] = 0x8000;
  gAmplitude[voice] = 0;
}

void synth::suspend() {
  TIMSK1 &= static_cast<uint8_t>(~_BV(OCIE1A));
}

void synth::resume() {
  TIMSK1 |= _BV(OCIE1A);
}

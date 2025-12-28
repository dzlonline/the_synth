/*
 * theSynth – 4-voice wavetable engine for AVR Arduinos
 * Copyright (c) 2014-2025 Dzl / Illutron
 * Licensed under the MIT License; see the LICENSE file for details.
 */

/**
 * @file synth.h
 * @brief Public API for the four-voice wavetable synthesizer.
 */

#pragma once

#include <Arduino.h>

#if !defined(__AVR__)
#error "the_synth presently supports AVR-based boards only"
#endif

#ifndef F_CPU
#error "F_CPU must be defined for theSynth library"
#endif

// Backwards compatible constants -------------------------------------------------------

constexpr uint8_t DIFF = 1;
constexpr uint8_t CHA = 2;
constexpr uint8_t CHB = 3;

constexpr uint8_t SINE = 0;
constexpr uint8_t TRIANGLE = 1;
constexpr uint8_t SQUARE = 2;
constexpr uint8_t SAW = 3;
constexpr uint8_t RAMP = 4;
constexpr uint8_t NOISE = 5;

constexpr uint8_t ENVELOPE0 = 0;
constexpr uint8_t ENVELOPE1 = 1;
constexpr uint8_t ENVELOPE2 = 2;
constexpr uint8_t ENVELOPE3 = 3;

class synth {
public:
  static constexpr uint8_t kVoiceCount = 4;
  static constexpr float kSampleRate = 20000.0f;

  synth() = default;

  void begin(uint8_t mode = CHA);
  bool synthTick();
  bool voiceFree(uint8_t voice) const;

  void setupVoice(uint8_t voice, uint8_t wave, uint8_t pitch,
                  uint8_t env, uint8_t length, uint8_t mod);

  void setWave(uint8_t voice, uint8_t wave);
  void setPitch(uint8_t voice, uint8_t midiNote);
  void setEnvelope(uint8_t voice, uint8_t env);
  void setLength(uint8_t voice, uint8_t length);
  void setMod(uint8_t voice, uint8_t mod);
  void mTrigger(uint8_t voice, uint8_t midiNote);
  void setFrequency(uint8_t voice, float frequencyHz);
  void setTime(uint8_t voice, float seconds);
  void trigger(uint8_t voice);
  void release(uint8_t voice);

  void suspend();
  void resume();

private:
  void configureOutput(uint8_t mode);
  void configureTimer();
  static bool isValidVoice(uint8_t voice);
};














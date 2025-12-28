# theSynth – 4-Voice Wavetable Engine for AVR Arduinos

theSynth is a compact, 20 kHz, four-voice wavetable synthesizer aimed at classic AVR-based Arduinos (Uno, Nano, Pro Mini, Mega, etc.). It produces audio through Timer2 PWM (pin-dependent) and exposes a lightweight API for setting waveforms, envelopes, modulation, and MIDI-triggered playback.

## Features
- 20 kHz interrupt-driven audio engine (Timer1) with ~45% CPU usage on Uno-class boards
- Four independent voices with selectable waveforms, envelopes, length, modulation, and MIDI/frequency helpers
- Multiple output modes: PIN11 (CHA), PIN3 (CHB), or differential (both) on Timer2 pins per MCU
- MIDI-friendly helpers (`mTrigger`, `setupVoice`, `synthTick`) plus direct frequency/time setters
- Suspend/resume hooks to free CPU time temporarily
- Examples covering arbitrary frequency control, modulation, MIDI parsing, pin modes, sequencing, and power management

## Supported Boards
| MCU | Boards | CHA pin (OC2A) | CHB pin (OC2B) |
| --- | --- | --- | --- |
| ATmega328P/PB, 168, 88, 48 | Uno, Nano, Pro Mini, Duemilanove | D11 | D3 |
| ATmega1280/2560 | Mega family | D10 | D9 |
| ATmega644P/1284P | Mighty Core boards | D7 | D6 |

> **Note**: Atmega32u4-based boards (Leonardo/Micro) lack Timer2 and are not currently supported. Non-AVR boards require a new driver backend.

## Installation
1. Copy/clone the repository so that `library.properties` and `src/` sit at the root.
2. Restart the Arduino IDE or run `arduino-cli lib install --git-url https://github.com/dzlonline/the_synth.git`.
3. Open an example from the `examples/` folder and select a supported board/FQBN.

## Wiring Cheat-Sheet
Low-pass filter the PWM output before feeding an amplifier/headphones:

```
Timer2 pin ---[1 kΩ]---+----||----> Audio Out
                       |   10 µF
                       === 10 nF
                       |
                      GND
```

Differential mode doubles swing by driving both pins through identical filters into a floating load.

## Basic Usage
```cpp
#include <synth.h>

synth edgar;

void setup() {
  edgar.begin(CHA);                                      // choose output mode
  edgar.setupVoice(0, SINE, 60, ENVELOPE1, 90, 64);      // voice, wave, MIDI, env, length, mod
  edgar.setupVoice(1, SAW, 64, ENVELOPE2, 80, 64);
}

void loop() {
  edgar.mTrigger(0, 60);                                 // MIDI note on
  edgar.setFrequency(1, 329.6f);                         // arbitrary Hz
  edgar.trigger(1);                                      // immediate trigger
  delay(400);
}
```

Key helpers:
- `begin(mode)` – configure timers/PWM output
- `setupVoice()` – bulk voice configuration
- `mTrigger()` / `trigger()` – MIDI or raw trigger
- `setWave`, `setPitch`, `setEnvelope`, `setLength`, `setMod` – individual parameters
- `synthTick()` – returns true every 4 audio frames for lightweight timing
- `suspend()` / `resume()` – pause/resume the audio ISR

## Modernization Notes
- Library now follows the standard Arduino layout (`src/`, `examples/`, `library.properties`), making it IDE/CLI and Library Manager friendly.
- Timer/pin configuration is abstracted per AVR family; `F_CPU` is honored, so 8 MHz boards auto-scale the sample rate divisor.
- ISR and global state live in `src/synth.cpp`, preventing multiple-definition issues and keeping `synth.h` lean.
- Constants remain compatible (e.g., `SINE`, `CHA`), but enums can be swapped in future releases without breaking sketches.
- README, keywords, and license files have been refreshed to reflect current capabilities.

## Roadmap
1. Add automated builds (GitHub Actions + arduino-cli) for Uno, Nano, Mega, and MightyCore boards.
2. Offer pluggable output drivers so non-Timer2 MCUs (e.g., ATmega32u4, modern ARM boards) can contribute custom backends.
3. Provide additional envelope and wavetable generation scripts plus documentation on crafting custom tables.

Contributions and bug reports are welcome—please include board type, sketch, and any oscilloscope captures or MIDI logs when filing issues.

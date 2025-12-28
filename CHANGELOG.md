# Changelog

All notable changes to this project will be documented in this file.

## [Unreleased]

_No changes yet._

## [1.5.0] - 2025-12-28

### Added
- Explicit MIT license headers in `src/synth.cpp`, `src/synth.h`, `src/tables.h`, and `examples/MIDI_synth/MIDI_parser.h`.
- This changelog to track future releases.

### Changed
- Legacy `synth` implementation replaced with a modern split between `src/synth.h` and `src/synth.cpp`, keeping the public API header lean.
- Library now follows the Arduino Library Manager layout (`src/`, `examples/`, `library.properties`, `keywords.txt`) and ships an updated README with board/pin tables and wiring notes.
- Example sketches refreshed (MIDI note-off handling, suspend/resume windowing) to match the updated engine behavior.

### Fixed
- Default argument for `synth::begin()` now resolves correctly by defining compatibility constants before the class declaration.

// Suspend/resume example demonstrating how to free CPU cycles when audio is not needed.

//Hardware connection(s): same low-pass filter shown in README.

#include <synth.h>

constexpr uint8_t kVoice = 0;
constexpr uint32_t kOnWindowMs = 4000;
constexpr uint32_t kOffWindowMs = 4000;

synth edgar;
bool audioRunning = true;
uint32_t lastNote = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  edgar.begin(DIFF);                         // run in differential mode
  edgar.setupVoice(kVoice, TRIANGLE, 60, ENVELOPE1, 80, 64);
}

void loop() {
  const uint32_t now = millis();

  // retrigger every second while audio is active
  if (audioRunning && now - lastNote > 1000) {
    edgar.mTrigger(kVoice, 60);
    lastNote = now;
  }

  // alternate between active/inactive windows without blocking delay()
  const uint32_t phase = now % (kOnWindowMs + kOffWindowMs);
  if (phase < kOnWindowMs) {
    if (!audioRunning) {
      edgar.resume();
      audioRunning = true;
      digitalWrite(LED_BUILTIN, HIGH);
    }
  } else {
    if (audioRunning) {
      edgar.suspend();
      audioRunning = false;
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
}







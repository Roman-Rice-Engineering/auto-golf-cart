#include "config.h"
#include "manual.h"

void setup() {
    pinMode(SWITCH_DRIVE_ENABLE_PIN, OUTPUT);
    digitalWrite(SWITCH_DRIVE_ENABLE_PIN, HIGH);
    manual_setup();
}

void loop() {
  manual_loop();
}

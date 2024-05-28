#include "manual.h"
#include "config.h"
#include <Arduino.h>

void manual_setup(void){
  pinMode(TURF_PIN, OUTPUT);
  pinMode(REVERSE_PIN, OUTPUT);
  pinMode(FORWARD_PIN, OUTPUT);
  pinMode(START_PIN, OUTPUT);

  pinMode(MAN_REVERSE_SWITCH_PIN, INPUT_PULLUP);
  pinMode(MAN_FORWARD_SWITCH_PIN, INPUT_PULLUP);
  pinMode(MAN_START_SWITCH_PIN, INPUT_PULLUP);
  
  digitalWrite(TURF_PIN, LOW);
  digitalWrite(REVERSE_PIN, LOW);
  digitalWrite(FORWARD_PIN, LOW);
  digitalWrite(START_PIN, LOW);
}

void manual_loop(void){
   digitalWrite(START_PIN, !((bool)digitalRead(MAN_START_SWITCH_PIN)));
   digitalWrite(TURF_PIN, !((bool)digitalRead(MAN_TURF_SWITCH_PIN)));
   digitalWrite(FORWARD_PIN, (((bool)digitalRead(MAN_FORWARD_SWITCH_PIN)) != FORWARD_REVERSE_OFF_STATE) ? HIGH : LOW);
   digitalWrite(REVERSE_PIN, (((bool)digitalRead(MAN_REVERSE_SWITCH_PIN)) != FORWARD_REVERSE_OFF_STATE) ? HIGH : LOW);
}

void manual_end(void){
  digitalWrite(TURF_PIN, LOW);
  digitalWrite(REVERSE_PIN, LOW);
  digitalWrite(FORWARD_PIN, LOW);
  digitalWrite(START_PIN, LOW);
}

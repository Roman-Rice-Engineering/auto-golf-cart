#include "config.h"
#include "manual.h"
#include "automatic.hpp"

bool automatic = false;

void setup() {
    pinMode(SWITCH_DRIVE_ENABLE_PIN, OUTPUT);
    digitalWrite(SWITCH_DRIVE_ENABLE_PIN, HIGH);
    manual_setup();
}

void loop() {
  bool new_automatic = digitalRead(MAN_AUTO_SELECT_PIN);

  if(new_automatic != automatic){
    automatic = new_automatic;
    if(automatic == true){
      manual_end();
      automatic_setup(BAUD_RATE);
    }else{
      automatic_end();
      manual_setup();
    }
  }
  
  if(automatic == false)
    manual_loop();
  else
    automatic_loop();
}

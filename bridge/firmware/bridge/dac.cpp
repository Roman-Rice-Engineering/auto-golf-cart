#include "dac.h"
#include <stdint.h>
#include <Arduino.h>

void dac_setup(void){
	DDRB = 255;
  PORTB = 0;
}

void dac_write(uint8_t val){
	PORTB = val/4;
}

void dac_end(void){
  PORTB = 0;
}

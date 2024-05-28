#include "dac.h"
#include <stdint.h>
#include <Arduino.h>
#include <SPI.h>

void dac_setup(void){
  pinMode(LDAC_PIN, OUTPUT);
  digitalWrite(LDAC_PIN, LOW);
  SPI.begin();
  dac_write(0);
}

/* 2 Byte transfer format:
 *  
 *  [0, 0, 1, 1, D7, D6, D5, D4] [D3, D2, D1, D0, 0, 0, 0, 0]
 * 
 * 
 */

void dac_write(uint8_t val){
  uint8_t first_byte = (val >> 4) | 0b00110000;
  uint8_t second_byte = val << 4;
  uint16_t to_transfer = (first_byte << 8) + second_byte;
  SPI.transfer16(to_transfer);
}

void dac_end(void){
  dac_write(0);
  SPI.end();
}

#ifndef DAC_H
#define DAC_H

#include <stdint.h>

#define LDAC_PIN 7

void dac_setup(void);
void dac_write(uint8_t val);
void dac_end(void);

#endif

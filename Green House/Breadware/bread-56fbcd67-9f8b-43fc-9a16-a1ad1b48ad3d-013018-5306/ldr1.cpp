/*
 * C Source File for Driver:
 *
 * Alias: "ldr1" 
 * Type: "bright_tsl2561"
 *
 * Generated from C source file with Python
 *
 * Built with BREAD
 */

#include "ldr1.h"

/* Required Values */ 

#include <math.h>

uint8_t ldr1_I2CADDR_DEFAULT = 0x29;

uint8_t ldr1_REGISTER_CONTROL = 0x00;
uint8_t ldr1_REGISTER_TIMING = 0x01;
uint8_t ldr1_REGISTER_CHAN0_LOW = 0x0C;
uint8_t ldr1_REGISTER_CHAN1_LOW = 0x0E;

uint8_t ldr1_REGISTER_ID = 0x09;
uint8_t ldr1_COMMAND_BIT = 0x80;
uint8_t ldr1_WORD_BIT = 0x20;
uint8_t ldr1_CONTROL_POWERON = 0x03;
uint8_t ldr1_SAMPLE_13MS = 0x00;

/**
 * Initialize the tsl2561 brightness sensor
 */
bool ldr1_init()
{
  i2c_start();

  i2c_write_byte(ldr1_I2CADDR_DEFAULT, ldr1_COMMAND_BIT | ldr1_REGISTER_CONTROL, 0x00);
  i2c_write_byte(ldr1_I2CADDR_DEFAULT, ldr1_COMMAND_BIT | ldr1_REGISTER_CONTROL, ldr1_CONTROL_POWERON);

  i2c_write_byte(ldr1_I2CADDR_DEFAULT, ldr1_COMMAND_BIT | ldr1_REGISTER_TIMING, ldr1_SAMPLE_13MS);

  if (i2c_read_byte(ldr1_I2CADDR_DEFAULT, ldr1_COMMAND_BIT | ldr1_REGISTER_CONTROL) != ldr1_CONTROL_POWERON) {
    return false;
  }
  return true;
}

/**
 * Return the brightness level in lux.
 *
 * NOTE: The read time for this sensor is approximately 13.7ms.
 *
 * Return the brightness level in lux from 0 lux to 40000 lux.
 */
float ldr1_read()
{
  bool enabled = ldr1_init();
  if (!enabled) {
    return 0;
  }

  delay_for_ms(14);

  uint16_t lux_int_ch0 = i2c_read_2_bytes(ldr1_I2CADDR_DEFAULT, ldr1_COMMAND_BIT | ldr1_WORD_BIT | ldr1_REGISTER_CHAN0_LOW);
  uint16_t lux_int_ch1 = i2c_read_2_bytes(ldr1_I2CADDR_DEFAULT, ldr1_COMMAND_BIT | ldr1_WORD_BIT | ldr1_REGISTER_CHAN1_LOW);

  float CH0 = lux_int_ch0 + 0.01;
  float CH1 = lux_int_ch1 + 0.01;
  float CH_fraction = CH1/CH0;

  float lux_val;
  if (CH_fraction <= 0.52) {
    lux_val = 0.0315*CH0-0.0593*CH0*(pow(CH_fraction,1.4));
  } else if (CH_fraction <= 0.65) {
    lux_val = 0.0229*CH0-0.0291*CH1;
  } else if (CH_fraction <= 0.80) {
    lux_val = 0.0157*CH0-0.018*CH1;
  } else if (CH_fraction <= 1.3) {
    lux_val = 0.00338*CH0-0.0026*CH1;
  } else {
    lux_val = 0;
  }

  return lux_val;
}

/* Define external alias */
struct ldr1_namespace const ldr1 = {
    ldr1_init,
    ldr1_read
};

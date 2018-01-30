/*
 * C Source File for Driver:
 *
 * Alias: "temp1" 
 * Type: "temp_lm75bd"
 *
 * Generated from C source file with Python
 *
 * Built with BREAD
 */

#include "temp1.h"

/* Required Values */ 

uint16_t temp1_I2CADDR_DEFAULT = 0x48;
uint16_t temp1_REG_TEMP = 0x00;

/**
 * Initialize the lm75bd driver
 */
bool temp1_init()
{
    i2c_start();
    if (i2c_read_2_bytes(temp1_I2CADDR_DEFAULT, temp1_REG_TEMP) == UINT16_MAX) {
      return false;
    }
    return true;
}

/**
 * Read temperature from the device in Celsius from -55C to 127C.
 *
 */
float temp1_read()
{
  bool enabled = temp1_init();
  if (!enabled) {
    return 0;
  }

  uint16_t temp_val = i2c_read_2_bytes(temp1_I2CADDR_DEFAULT, temp1_REG_TEMP);
  return (temp_val >> 5) / 8.0;
}

/* Define external alias */
struct temp1_namespace const temp1 = {
    temp1_init,
    temp1_read
};

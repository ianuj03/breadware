/*
 * C Source File for Driver:
 *
 * Alias: "g1" 
 * Type: "gyro_l3gd20"
 *
 * Generated from C source file with Python
 *
 * Built with BREAD
 */

#include "g1.h"

/* Required Values */ 

uint8_t g1_I2CADDR_DEFAULT = 0x6A;

uint8_t g1_ID = 0xD4;
uint8_t g1_H_ID = 0xD7;

uint8_t g1_CTRL_REG_GENERAL = 0x20;

uint8_t g1_CTRL_REG_FILTER_MODE  = 0x21;

uint8_t g1_CTRL_REG_RESOLUTION  = 0x23;

uint8_t g1_WHO_AM_I = 0x0F;

uint8_t g1_OUT_X_L  = 0x28;
uint8_t g1_OUT_X_H  = 0x29;
uint8_t g1_OUT_Y_L  = 0x2A;
uint8_t g1_OUT_Y_H  = 0x2B;
uint8_t g1_OUT_Z_L  = 0x2C;
uint8_t g1_OUT_Z_H  = 0x2D;

uint8_t g1_REG_GENERAL_DEFAULT = 0x0F;

uint8_t g1_REG_RESOLUTION_DEFAULT = 0x00;
float g1_REG_RESOLUTION_MULTIPLIER_DEFAULT = 0.00875F;

bool g1_init()
{
  i2c_start();

  uint8_t id = i2c_read_byte_with_delay(g1_I2CADDR_DEFAULT, g1_WHO_AM_I, 2);
  if ((id != g1_ID) && (id != g1_H_ID)) {
      return false;
  }

  i2c_write_byte(g1_I2CADDR_DEFAULT, g1_CTRL_REG_GENERAL, g1_REG_GENERAL_DEFAULT);
  i2c_write_byte(g1_I2CADDR_DEFAULT, g1_CTRL_REG_RESOLUTION, g1_REG_RESOLUTION_DEFAULT);

  return true;
}

/**
 * Converts the raw numeric output from the gyroscope into units of degs/sec. The inputs to the function are the raw numeric reading from the gyroscope and the resolution setting of the gyroscope: 8.75 mdps/digit, 17.50 mdps/digit, 70 mdps/digit.
 */
float g1_get_degrees(uint8_t lo, uint8_t hi, float resolution) {
  int16_t val = (int16_t)(lo | (hi << 8));
  return val * resolution;
}

/**
 * Read rotational acceleration about the x-axis of the device from -2000 to +2000 in units of \f$ degs/sec \f$
 *
 */
float g1_read_x()
{
  bool enabled = g1_init();
  if (!enabled) {
    return 0;
  }
  delay_for_ms(2);
  uint8_t lo = i2c_read_byte_with_delay(g1_I2CADDR_DEFAULT , g1_OUT_X_L, 2);
  uint8_t hi = i2c_read_byte_with_delay(g1_I2CADDR_DEFAULT , g1_OUT_X_H, 2);
  return g1_get_degrees(lo, hi, g1_REG_RESOLUTION_MULTIPLIER_DEFAULT);
}

/**
 * Read rotational acceleration about the y-axis of the device from -2000 to +2000 in units of \f$ degs/sec \f$
 *
 */
float g1_read_y()
{
  bool enabled = g1_init();
  if (!enabled) {
    return 0;
  }
  delay_for_ms(2);
  uint8_t lo = i2c_read_byte_with_delay(g1_I2CADDR_DEFAULT , g1_OUT_Y_L, 2);
  uint8_t hi = i2c_read_byte_with_delay(g1_I2CADDR_DEFAULT , g1_OUT_Y_H, 2);
  return g1_get_degrees(lo, hi, g1_REG_RESOLUTION_MULTIPLIER_DEFAULT);
}

/**
 * Read rotational acceleration about the z-axis of the device from -2000 to +2000 in units of \f$ degs/sec \f$
 *
 */
float g1_read_z()
{
  bool enabled = g1_init();
  if (!enabled) {
    return 0;
  }
  delay_for_ms(2);
  uint8_t lo = i2c_read_byte_with_delay(g1_I2CADDR_DEFAULT , g1_OUT_Z_L, 2);
  uint8_t hi = i2c_read_byte_with_delay(g1_I2CADDR_DEFAULT , g1_OUT_Z_H, 2);
  return g1_get_degrees(lo, hi, g1_REG_RESOLUTION_MULTIPLIER_DEFAULT);
}

/* Define external alias */
struct g1_namespace const g1 = {
    g1_init,
    g1_read_x,
    g1_read_y,
    g1_read_z
};

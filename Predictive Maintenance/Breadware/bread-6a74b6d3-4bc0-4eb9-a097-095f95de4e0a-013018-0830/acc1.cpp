/*
 * C Source File for Driver:
 *
 * Alias: "acc1" 
 * Type: "accel_mma8652"
 *
 * Generated from C source file with Python
 *
 * Built with BREAD
 */

#include "acc1.h"

/* Required Values */ 

uint8_t acc1_MMA8653_I2C_ADDR = 0x1D;

uint8_t acc1_MMA8653_DEVICE_ID = 0x5A;

uint8_t acc1_MMA8653_REG__STATUS = 0x00;

uint8_t acc1_MMA8653_REG__OUT_X_MSB = 0x01;

uint8_t acc1_MMA8653_REG__OUT_X_LSB = 0x02;

uint8_t acc1_MMA8653_REG__OUT_Y_MSB = 0x03;

uint8_t acc1_MMA8653_REG__OUT_Y_LSB = 0x04;

uint8_t acc1_MMA8653_REG__OUT_Z_MSB = 0x05;

uint8_t acc1_MMA8653_REG__OUT_Z_LSB = 0x06;

uint8_t acc1_MMA8653_REG__WHO_AM_I = 0x0D;

uint8_t acc1_MMA8653_REG__XYZ_DATA_CFG = 0x0E;

uint8_t acc1_MMA8653_REG__CTRL_REG1 = 0x2A;

uint8_t acc1_MMA8653_REG__CTRL_REG2 = 0x2B;

uint8_t acc1_MMA8653_REG__CTRL_REG3 = 0x2C;

uint8_t acc1_MMA8653_REG__CTRL_REG4 = 0x2D;

uint8_t acc1_MMA8653_REG__CTRL_REG5 = 0x2E;

/**
 * Stop sampling from the accelerometer
 *
 * NOTE: This must be called before writing changes to registers.
 */
void acc1_stop_sampling()
{
  i2c_write_byte(acc1_MMA8653_I2C_ADDR, acc1_MMA8653_REG__CTRL_REG1, 0x00);
}

/**
 * Start sampling the accelerometer
 *
 * Data Rate: 800HZ
 */
void acc1_start_sampling()
{
  i2c_write_byte(acc1_MMA8653_I2C_ADDR, acc1_MMA8653_REG__CTRL_REG1, 0x49);
}

/**
 * Convert accelerometer 8 byte value to meters per second.
 *
 * @param val The 8 byte value from the accelerometer.
 *
 * @return: The converted meters per second
 */
float acc1_accelValToMetersPerSecond (int16_t val) {
  return (val / 1024.0) * 9.81;
}

/**
 * Initialize the MMA8653 accelerometer.
 *
 * Startup Process
 * ####################
 *
 * 1. Turn the accelerometer into standby mode
 * 2. Set the data polling and accuracy settings.
 * 3. Configure interrupts:
 *    a) Open drain (continuous output)
 *    b) Pulse, orientation, free fall triggers
 * 4. Re-enable sample mode on the accelerometer
 *
 */
bool acc1_init() {
  i2c_start();

  uint8_t id[1];
  i2c_read_length(acc1_MMA8653_I2C_ADDR, acc1_MMA8653_REG__WHO_AM_I, id, 1);

  if (id[0] != acc1_MMA8653_DEVICE_ID) {
    return false;
  }
  acc1_start_sampling();
  return true;
}

/**
 * Read the 2 byte pair vector register starting at the MSB provided
 */
int16_t acc1__readVector(uint8_t startReg)
{
  bool enabled = acc1_init();
  if (!enabled) {
    return 0;
  }

  uint8_t data[2];
  i2c_read_length(acc1_MMA8653_I2C_ADDR, startReg, data, 2);

  uint16_t val = ((data[0] << 8) | data[1]) >> 4;

  if (data[1] > 127) {
    val = -1 * (~val + 1);
  }
  return val;
}

/**
 * Read the x-axis linear acceleration from the device from -8g to +8g in \f$ m / s^2 \f$
 */
float acc1_read_x()
{
  int16_t x = acc1__readVector(acc1_MMA8653_REG__OUT_X_MSB);
  return acc1_accelValToMetersPerSecond(x);
}

/**
 * Read the y-axis linear acceleration from the device from -8g to +8g in \f$ m / s^2 \f$
 */
float acc1_read_y()
{
  int16_t y = acc1__readVector(acc1_MMA8653_REG__OUT_Y_MSB);
  return acc1_accelValToMetersPerSecond(y);
}

/**
 * Read the z-axis linear acceleration from the device from -8g to +8g in \f$ m / s^2 \f$
 */
float acc1_read_z()
{
  int16_t z = acc1__readVector(acc1_MMA8653_REG__OUT_Z_MSB);
  return acc1_accelValToMetersPerSecond(z);
}

/* Define external alias */
struct acc1_namespace const acc1 = {
    acc1_init,
    acc1_read_x,
    acc1_read_y,
    acc1_read_z
};

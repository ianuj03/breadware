/*
 * C Source File for Driver:
 *
 * Alias: "humidity1" 
 * Type: "humid_hdc1080"
 *
 * Generated from C source file with Python
 *
 * Built with BREAD
 */

#include "humidity1.h"

/* Required Values */ 

uint8_t humidity1_i2caddr = 0x40;

uint8_t humidity1_temperature   = 0x00;
uint8_t humidity1_humidity      = 0x01;
uint8_t humidity1_configuration = 0x02;
uint8_t humidity1_id0           = 0xFB;
uint8_t humidity1_id1           = 0xFC;
uint8_t humidity1_id2           = 0xFD;
uint8_t humidity1_manufid       = 0xFE;
uint8_t humidity1_devid         = 0xFF;

const uint8_t humidity1_READ_DELAY_MS = 9;

/**
 * Initialize the humidity sensor
 *
 */
bool humidity1_init()
{
  i2c_start();
  if (i2c_read_2_bytes_with_delay(humidity1_i2caddr, humidity1_humidity, humidity1_READ_DELAY_MS) == 0xFFFF) {
    return false;
  }

    return true;
}

/**
 * Read the relative humidity as percentage (%).
 *
 */
float humidity1_read()
{
  bool enabled = humidity1_init();
  if (!enabled) {
    return 0;
  }

  uint16_t humidity_val = i2c_read_2_bytes_with_delay(humidity1_i2caddr, humidity1_humidity, humidity1_READ_DELAY_MS);

  float humid_percent = humidity_val >> 8;

  humid_percent = (humid_percent * 100) / 256;
  return humid_percent;
}

/* Define external alias */
struct humidity1_namespace const humidity1 = {
    humidity1_init,
    humidity1_read
};

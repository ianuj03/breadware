/*
 * C Source File for Driver:
 *
 * Alias: "speaker1" 
 * Type: "speaker"
 *
 * Generated from C source file with Python
 *
 * Built with BREAD
 */

#include "speaker1.h"

/* Required Values */ 
uint8_t const PIN = 65;

bool speaker1_init()
{
  gpio_set_output(PIN);
  return true;
}

/**
 * Output a tone at a desired frequency.
 *
 * @param frequency_hz the frequency of the desired output tone. Range: 20Hz to 20000Hz. Use 0 for off.
 */
void speaker1_write(int frequency_hz)
{
  if (frequency_hz == 0) {
    gpio_pwm(PIN, 100, 1);
  } else {
    gpio_pwm(PIN, frequency_hz, 0);
  }
}

/* Define external alias */
struct speaker1_namespace const speaker1 = {
    speaker1_init,
    speaker1_write
};

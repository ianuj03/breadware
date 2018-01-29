/*
 * C Source File for Driver:
 *
 * Alias: "mic1" 
 * Type: "mic_max4466"
 *
 * Generated from C source file with Python
 *
 * Built with BREAD
 */

#include "mic1.h"

/* Required Values */ 
uint16_t const PIN = 65;

bool mic1_init()
{
  gpio_set_input(PIN);

  return true;
}

/**
 * Return the sound volume sensed by the microphone in dB. Specifically, this function returns the peak-to-peak sound amplitude of a 50ms sample window.
 */
uint16_t mic1_read()
{
  long startMillis = time_ms();
  unsigned int peakToPeak = 0;
  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

  int c = 0;

    while (time_ms() - startMillis < 50) {

    c++;

    int sample = (int)gpio_analog_read(PIN);
    if (sample < 1024)
      {
        if (sample > signalMax)
      {
        signalMax = sample;
      }
      else if (sample < signalMin) {
        signalMin = sample;
      }
    }
  }

  peakToPeak = signalMax - signalMin;

  return (peakToPeak * 3.3) / 1024 * 30;
}

/* Define external alias */
struct mic1_namespace const mic1 = {
    mic1_init,
    mic1_read
};

/*
 * C Source File for Driver:
 *
 * Alias: "led1" 
 * Type: "led_ws2812"
 *
 * Generated from C source file with Python
 *
 * Built with BREAD
 */

#include "led1.h"

/* Required Values */ 
int8_t const PIN = 66;

#include <stdlib.h>
#include <string.h>

#ifdef __AVR__
#include "Arduino.h"
#endif

uint8_t *led1_pixels;
uint32_t led1_endTime;

volatile uint8_t *led1_port;
uint8_t led1_pinMask;
uint8_t led1_currentRed = 0;
uint8_t led1_currentGreen = 0;
uint8_t led1_currentBlue = 0;

inline bool led1_canShow(void) {
  return (get_micros() - led1_endTime) >= 300L;
}

bool led1_init()
{
  if((led1_pixels = (uint8_t *)malloc(3))) {
    memset(led1_pixels, 0, 3);
  }
  gpio_write(PIN, false);

  volatile uint8_t *our_port;
  uint8_t our_pinMask;

#ifdef __AVR__
  our_port = portOutputRegister(digitalPinToPort(PIN));
  our_pinMask = digitalPinToBitMask(PIN);
#endif
  led1_port = our_port;
  led1_pinMask = our_pinMask;

  return true;
}

 /**
  * Turns on the LED to a certain color using a RGB color model.
  *
  * @param red Intensity of the color RED as an integer between 0 and 255.
  * @param green Intensity of the color GREEN as an integer between 0 and 255.
  * @param blue Intensity of the color BLUE as an integer between 0 and 255.
  */
void led1_setRGB(uint8_t red, uint8_t green, uint8_t blue) {
  if (led1_currentRed == red &&
      led1_currentGreen == green &&
      led1_currentBlue == blue) {
    return;
  } else {
    led1_currentRed = red;
    led1_currentGreen = green;
    led1_currentBlue = blue;
  }

uint8_t
  wOffset = (((1 << 6) | (1 << 4) | (0 << 2) | (2))>> 6) & 0b11,
  rOffset = (((1 << 6) | (1 << 4) | (0 << 2) | (2))>> 4) & 0b11,
  gOffset = (((1 << 6) | (1 << 4) | (0 << 2) | (2))>> 2) & 0b11,
  bOffset =  ((1 << 6) | (1 << 4) | (0 << 2) | (2))      & 0b11;

  uint8_t *p;
  p = &led1_pixels[0];

  p[rOffset] = red;
  p[gOffset] = green;
  p[bOffset] = blue;

  if(!led1_pixels) {
    return;
  }

  while(!led1_canShow());

  volatile uint16_t
    i   = 3;
  volatile uint8_t
   *ptr = led1_pixels,
    b   = *ptr++,
    hi,
    lo;

    volatile uint8_t next, bit;

    hi   = *led1_port |  led1_pinMask;
    lo   = *led1_port & ~led1_pinMask;
    next = lo;
    bit  = 8;

    volatile uint8_t *our_port = led1_port;

    #ifdef __AVR__
    asm volatile(
     "head66:"                   "\n\t"
      "st   %a[port_num],  %[hi]"    "\n\t"
      "sbrc %[byte],  7"         "\n\t"
       "mov  %[next], %[hi]"     "\n\t"
      "dec  %[bit]"              "\n\t"
      "st   %a[port_num],  %[next]"  "\n\t"
      "mov  %[next] ,  %[lo]"    "\n\t"
      "breq nextbyte66"          "\n\t"
      "rol  %[byte]"             "\n\t"
      "rjmp .+0"                 "\n\t"
      "nop"                      "\n\t"
      "st   %a[port_num],  %[lo]"    "\n\t"
      "nop"                      "\n\t"
      "rjmp .+0"                 "\n\t"
      "rjmp head66"              "\n\t"
     "nextbyte66:"               "\n\t"
      "ldi  %[bit]  ,  8"        "\n\t"
      "ld   %[byte] ,  %a[ptr]+" "\n\t"
      "st   %a[port_num], %[lo]"     "\n\t"
      "nop"                      "\n\t"
      "sbiw %[count], 1"         "\n\t"
       "brne head66"             "\n"
      : [port_num]  "+e" (our_port),
        [byte]  "+r" (b),
        [bit]   "+r" (bit),
        [next]  "+r" (next),
        [count] "+w" (i)
      : [ptr]    "e" (ptr),
        [hi]     "r" (hi),
        [lo]     "r" (lo)
);
#endif

  led1_endTime = get_micros();
}

/**
 * Turns off the LED.
 */
void led1_off() {
  led1_setRGB(0, 0, 0);
}

/* Define external alias */
struct led1_namespace const led1 = {
    led1_init,
    led1_setRGB,
    led1_off
};

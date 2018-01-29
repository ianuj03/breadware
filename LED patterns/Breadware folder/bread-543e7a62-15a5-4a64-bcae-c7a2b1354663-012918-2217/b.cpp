/*
 * C Source File for Driver:
 *
 * Alias: "b" 
 * Type: "led_ws2812"
 *
 * Generated from C source file with Python
 *
 * Built with BREAD
 */

#include "b.h"

/* Required Values */ 
int8_t const PIN = 67;

#include <stdlib.h>
#include <string.h>

#ifdef __AVR__
#include "Arduino.h"
#endif

uint8_t *b_pixels;
uint32_t b_endTime;

volatile uint8_t *b_port;
uint8_t b_pinMask;
uint8_t b_currentRed = 0;
uint8_t b_currentGreen = 0;
uint8_t b_currentBlue = 0;

inline bool b_canShow(void) {
  return (get_micros() - b_endTime) >= 300L;
}

bool b_init()
{
  if((b_pixels = (uint8_t *)malloc(3))) {
    memset(b_pixels, 0, 3);
  }
  gpio_write(PIN, false);

  volatile uint8_t *our_port;
  uint8_t our_pinMask;

#ifdef __AVR__
  our_port = portOutputRegister(digitalPinToPort(PIN));
  our_pinMask = digitalPinToBitMask(PIN);
#endif
  b_port = our_port;
  b_pinMask = our_pinMask;

  return true;
}

 /**
  * Turns on the LED to a certain color using a RGB color model.
  *
  * @param red Intensity of the color RED as an integer between 0 and 255.
  * @param green Intensity of the color GREEN as an integer between 0 and 255.
  * @param blue Intensity of the color BLUE as an integer between 0 and 255.
  */
void b_setRGB(uint8_t red, uint8_t green, uint8_t blue) {
  if (b_currentRed == red &&
      b_currentGreen == green &&
      b_currentBlue == blue) {
    return;
  } else {
    b_currentRed = red;
    b_currentGreen = green;
    b_currentBlue = blue;
  }

uint8_t
  wOffset = (((1 << 6) | (1 << 4) | (0 << 2) | (2))>> 6) & 0b11,
  rOffset = (((1 << 6) | (1 << 4) | (0 << 2) | (2))>> 4) & 0b11,
  gOffset = (((1 << 6) | (1 << 4) | (0 << 2) | (2))>> 2) & 0b11,
  bOffset =  ((1 << 6) | (1 << 4) | (0 << 2) | (2))      & 0b11;

  uint8_t *p;
  p = &b_pixels[0];

  p[rOffset] = red;
  p[gOffset] = green;
  p[bOffset] = blue;

  if(!b_pixels) {
    return;
  }

  while(!b_canShow());

  volatile uint16_t
    i   = 3;
  volatile uint8_t
   *ptr = b_pixels,
    b   = *ptr++,
    hi,
    lo;

    volatile uint8_t next, bit;

    hi   = *b_port |  b_pinMask;
    lo   = *b_port & ~b_pinMask;
    next = lo;
    bit  = 8;

    volatile uint8_t *our_port = b_port;

    #ifdef __AVR__
    asm volatile(
     "head67:"                   "\n\t"
      "st   %a[port_num],  %[hi]"    "\n\t"
      "sbrc %[byte],  7"         "\n\t"
       "mov  %[next], %[hi]"     "\n\t"
      "dec  %[bit]"              "\n\t"
      "st   %a[port_num],  %[next]"  "\n\t"
      "mov  %[next] ,  %[lo]"    "\n\t"
      "breq nextbyte67"          "\n\t"
      "rol  %[byte]"             "\n\t"
      "rjmp .+0"                 "\n\t"
      "nop"                      "\n\t"
      "st   %a[port_num],  %[lo]"    "\n\t"
      "nop"                      "\n\t"
      "rjmp .+0"                 "\n\t"
      "rjmp head67"              "\n\t"
     "nextbyte67:"               "\n\t"
      "ldi  %[bit]  ,  8"        "\n\t"
      "ld   %[byte] ,  %a[ptr]+" "\n\t"
      "st   %a[port_num], %[lo]"     "\n\t"
      "nop"                      "\n\t"
      "sbiw %[count], 1"         "\n\t"
       "brne head67"             "\n"
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

  b_endTime = get_micros();
}

/**
 * Turns off the LED.
 */
void b_off() {
  b_setRGB(0, 0, 0);
}

/* Define external alias */
struct b_namespace const b = {
    b_init,
    b_setRGB,
    b_off
};

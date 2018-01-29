/*
 * C Source File for Driver:
 *
 * Alias: "c" 
 * Type: "led_ws2812"
 *
 * Generated from C source file with Python
 *
 * Built with BREAD
 */

#include "c.h"

/* Required Values */ 
int8_t const PIN = 7;

#include <stdlib.h>
#include <string.h>

#ifdef __AVR__
#include "Arduino.h"
#endif

uint8_t *c_pixels;
uint32_t c_endTime;

volatile uint8_t *c_port;
uint8_t c_pinMask;
uint8_t c_currentRed = 0;
uint8_t c_currentGreen = 0;
uint8_t c_currentBlue = 0;

inline bool c_canShow(void) {
  return (get_micros() - c_endTime) >= 300L;
}

bool c_init()
{
  if((c_pixels = (uint8_t *)malloc(3))) {
    memset(c_pixels, 0, 3);
  }
  gpio_write(PIN, false);

  volatile uint8_t *our_port;
  uint8_t our_pinMask;

#ifdef __AVR__
  our_port = portOutputRegister(digitalPinToPort(PIN));
  our_pinMask = digitalPinToBitMask(PIN);
#endif
  c_port = our_port;
  c_pinMask = our_pinMask;

  return true;
}

 /**
  * Turns on the LED to a certain color using a RGB color model.
  *
  * @param red Intensity of the color RED as an integer between 0 and 255.
  * @param green Intensity of the color GREEN as an integer between 0 and 255.
  * @param blue Intensity of the color BLUE as an integer between 0 and 255.
  */
void c_setRGB(uint8_t red, uint8_t green, uint8_t blue) {
  if (c_currentRed == red &&
      c_currentGreen == green &&
      c_currentBlue == blue) {
    return;
  } else {
    c_currentRed = red;
    c_currentGreen = green;
    c_currentBlue = blue;
  }

uint8_t
  wOffset = (((1 << 6) | (1 << 4) | (0 << 2) | (2))>> 6) & 0b11,
  rOffset = (((1 << 6) | (1 << 4) | (0 << 2) | (2))>> 4) & 0b11,
  gOffset = (((1 << 6) | (1 << 4) | (0 << 2) | (2))>> 2) & 0b11,
  bOffset =  ((1 << 6) | (1 << 4) | (0 << 2) | (2))      & 0b11;

  uint8_t *p;
  p = &c_pixels[0];

  p[rOffset] = red;
  p[gOffset] = green;
  p[bOffset] = blue;

  if(!c_pixels) {
    return;
  }

  while(!c_canShow());

  volatile uint16_t
    i   = 3;
  volatile uint8_t
   *ptr = c_pixels,
    b   = *ptr++,
    hi,
    lo;

    volatile uint8_t next, bit;

    hi   = *c_port |  c_pinMask;
    lo   = *c_port & ~c_pinMask;
    next = lo;
    bit  = 8;

    volatile uint8_t *our_port = c_port;

    #ifdef __AVR__
    asm volatile(
     "head7:"                   "\n\t"
      "st   %a[port_num],  %[hi]"    "\n\t"
      "sbrc %[byte],  7"         "\n\t"
       "mov  %[next], %[hi]"     "\n\t"
      "dec  %[bit]"              "\n\t"
      "st   %a[port_num],  %[next]"  "\n\t"
      "mov  %[next] ,  %[lo]"    "\n\t"
      "breq nextbyte7"          "\n\t"
      "rol  %[byte]"             "\n\t"
      "rjmp .+0"                 "\n\t"
      "nop"                      "\n\t"
      "st   %a[port_num],  %[lo]"    "\n\t"
      "nop"                      "\n\t"
      "rjmp .+0"                 "\n\t"
      "rjmp head7"              "\n\t"
     "nextbyte7:"               "\n\t"
      "ldi  %[bit]  ,  8"        "\n\t"
      "ld   %[byte] ,  %a[ptr]+" "\n\t"
      "st   %a[port_num], %[lo]"     "\n\t"
      "nop"                      "\n\t"
      "sbiw %[count], 1"         "\n\t"
       "brne head7"             "\n"
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

  c_endTime = get_micros();
}

/**
 * Turns off the LED.
 */
void c_off() {
  c_setRGB(0, 0, 0);
}

/* Define external alias */
struct c_namespace const c = {
    c_init,
    c_setRGB,
    c_off
};

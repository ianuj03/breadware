/*
 * C Source File for Driver:
 *
 * Alias: "a" 
 * Type: "led_ws2812"
 *
 * Generated from C source file with Python
 *
 * Built with BREAD
 */

#include "a.h"

/* Required Values */ 
int8_t const PIN = 69;

#include <stdlib.h>
#include <string.h>

#ifdef __AVR__
#include "Arduino.h"
#endif

uint8_t *a_pixels;
uint32_t a_endTime;

volatile uint8_t *a_port;
uint8_t a_pinMask;
uint8_t a_currentRed = 0;
uint8_t a_currentGreen = 0;
uint8_t a_currentBlue = 0;

inline bool a_canShow(void) {
  return (get_micros() - a_endTime) >= 300L;
}

bool a_init()
{
  if((a_pixels = (uint8_t *)malloc(3))) {
    memset(a_pixels, 0, 3);
  }
  gpio_write(PIN, false);

  volatile uint8_t *our_port;
  uint8_t our_pinMask;

#ifdef __AVR__
  our_port = portOutputRegister(digitalPinToPort(PIN));
  our_pinMask = digitalPinToBitMask(PIN);
#endif
  a_port = our_port;
  a_pinMask = our_pinMask;

  return true;
}

 /**
  * Turns on the LED to a certain color using a RGB color model.
  *
  * @param red Intensity of the color RED as an integer between 0 and 255.
  * @param green Intensity of the color GREEN as an integer between 0 and 255.
  * @param blue Intensity of the color BLUE as an integer between 0 and 255.
  */
void a_setRGB(uint8_t red, uint8_t green, uint8_t blue) {
  if (a_currentRed == red &&
      a_currentGreen == green &&
      a_currentBlue == blue) {
    return;
  } else {
    a_currentRed = red;
    a_currentGreen = green;
    a_currentBlue = blue;
  }

uint8_t
  wOffset = (((1 << 6) | (1 << 4) | (0 << 2) | (2))>> 6) & 0b11,
  rOffset = (((1 << 6) | (1 << 4) | (0 << 2) | (2))>> 4) & 0b11,
  gOffset = (((1 << 6) | (1 << 4) | (0 << 2) | (2))>> 2) & 0b11,
  bOffset =  ((1 << 6) | (1 << 4) | (0 << 2) | (2))      & 0b11;

  uint8_t *p;
  p = &a_pixels[0];

  p[rOffset] = red;
  p[gOffset] = green;
  p[bOffset] = blue;

  if(!a_pixels) {
    return;
  }

  while(!a_canShow());

  volatile uint16_t
    i   = 3;
  volatile uint8_t
   *ptr = a_pixels,
    b   = *ptr++,
    hi,
    lo;

    volatile uint8_t next, bit;

    hi   = *a_port |  a_pinMask;
    lo   = *a_port & ~a_pinMask;
    next = lo;
    bit  = 8;

    volatile uint8_t *our_port = a_port;

    #ifdef __AVR__
    asm volatile(
     "head69:"                   "\n\t"
      "st   %a[port_num],  %[hi]"    "\n\t"
      "sbrc %[byte],  7"         "\n\t"
       "mov  %[next], %[hi]"     "\n\t"
      "dec  %[bit]"              "\n\t"
      "st   %a[port_num],  %[next]"  "\n\t"
      "mov  %[next] ,  %[lo]"    "\n\t"
      "breq nextbyte69"          "\n\t"
      "rol  %[byte]"             "\n\t"
      "rjmp .+0"                 "\n\t"
      "nop"                      "\n\t"
      "st   %a[port_num],  %[lo]"    "\n\t"
      "nop"                      "\n\t"
      "rjmp .+0"                 "\n\t"
      "rjmp head69"              "\n\t"
     "nextbyte69:"               "\n\t"
      "ldi  %[bit]  ,  8"        "\n\t"
      "ld   %[byte] ,  %a[ptr]+" "\n\t"
      "st   %a[port_num], %[lo]"     "\n\t"
      "nop"                      "\n\t"
      "sbiw %[count], 1"         "\n\t"
       "brne head69"             "\n"
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

  a_endTime = get_micros();
}

/**
 * Turns off the LED.
 */
void a_off() {
  a_setRGB(0, 0, 0);
}

/* Define external alias */
struct a_namespace const a = {
    a_init,
    a_setRGB,
    a_off
};

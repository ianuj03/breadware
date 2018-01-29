/*
 * C Source File for Driver:
 *
 * Alias: "button1" 
 * Type: "button"
 *
 * Generated from C source file with Python
 *
 * Built with BREAD
 */

#include "button1.h"

/* Required Values */ 
uint16_t const pin = 62;

bool button1_init()
{
  return true;
}

/**
 * Return true for when the button is depressed; false otherwise
 */
uint16_t button1_is_pressed()
{
  return !gpio_read(pin);
}

/* Define external alias */
struct button1_namespace const button1 = {
    button1_init,
    button1_is_pressed
};

#ifndef a_H
#define a_H

/*
 * Header File for Driver:
 *
 * Alias: "a" 
 * Type: "led_ws2812"
 *
 * Generated from C source file with Python
 *
 * Built with BREAD
 */

#include "hal.h"

struct a_namespace {
    bool (*init)();
    void (*setRGB)(uint8_t, uint8_t, uint8_t);
    void (*off)();
};

extern struct a_namespace const a;

#endif /* a_H */

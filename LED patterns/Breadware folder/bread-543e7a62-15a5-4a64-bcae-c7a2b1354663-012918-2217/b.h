#ifndef b_H
#define b_H

/*
 * Header File for Driver:
 *
 * Alias: "b" 
 * Type: "led_ws2812"
 *
 * Generated from C source file with Python
 *
 * Built with BREAD
 */

#include "hal.h"

struct b_namespace {
    bool (*init)();
    void (*setRGB)(uint8_t, uint8_t, uint8_t);
    void (*off)();
};

extern struct b_namespace const b;

#endif /* b_H */

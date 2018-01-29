#ifndef c_H
#define c_H

/*
 * Header File for Driver:
 *
 * Alias: "c" 
 * Type: "led_ws2812"
 *
 * Generated from C source file with Python
 *
 * Built with BREAD
 */

#include "hal.h"

struct c_namespace {
    bool (*init)();
    void (*setRGB)(uint8_t, uint8_t, uint8_t);
    void (*off)();
};

extern struct c_namespace const c;

#endif /* c_H */

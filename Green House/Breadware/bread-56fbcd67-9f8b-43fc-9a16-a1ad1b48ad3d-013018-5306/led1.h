#ifndef led1_H
#define led1_H

/*
 * Header File for Driver:
 *
 * Alias: "led1" 
 * Type: "led_ws2812"
 *
 * Generated from C source file with Python
 *
 * Built with BREAD
 */

#include "hal.h"

struct led1_namespace {
    bool (*init)();
    void (*setRGB)(uint8_t, uint8_t, uint8_t);
    void (*off)();
};

extern struct led1_namespace const led1;

#endif /* led1_H */

#ifndef button1_H
#define button1_H

/*
 * Header File for Driver:
 *
 * Alias: "button1" 
 * Type: "button"
 *
 * Generated from C source file with Python
 *
 * Built with BREAD
 */

#include "hal.h"

struct button1_namespace {
    bool (*init)();
    uint16_t (*is_pressed)();
};

extern struct button1_namespace const button1;

#endif /* button1_H */

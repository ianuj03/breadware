#ifndef ldr1_H
#define ldr1_H

/*
 * Header File for Driver:
 *
 * Alias: "ldr1" 
 * Type: "bright_tsl2561"
 *
 * Generated from C source file with Python
 *
 * Built with BREAD
 */

#include "hal.h"

struct ldr1_namespace {
    bool (*init)();
    float (*read)();
};

extern struct ldr1_namespace const ldr1;

#endif /* ldr1_H */

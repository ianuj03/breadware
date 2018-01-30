#ifndef temp1_H
#define temp1_H

/*
 * Header File for Driver:
 *
 * Alias: "temp1" 
 * Type: "temp_lm75bd"
 *
 * Generated from C source file with Python
 *
 * Built with BREAD
 */

#include "hal.h"

struct temp1_namespace {
    bool (*init)();
    float (*read)();
};

extern struct temp1_namespace const temp1;

#endif /* temp1_H */

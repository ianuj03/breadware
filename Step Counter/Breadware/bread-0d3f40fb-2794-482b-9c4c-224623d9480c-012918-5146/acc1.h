#ifndef acc1_H
#define acc1_H

/*
 * Header File for Driver:
 *
 * Alias: "acc1" 
 * Type: "accel_mma8652"
 *
 * Generated from C source file with Python
 *
 * Built with BREAD
 */

#include "hal.h"

struct acc1_namespace {
    bool (*init)();
    float (*read_x)();
    float (*read_y)();
    float (*read_z)();
};

extern struct acc1_namespace const acc1;

#endif /* acc1_H */

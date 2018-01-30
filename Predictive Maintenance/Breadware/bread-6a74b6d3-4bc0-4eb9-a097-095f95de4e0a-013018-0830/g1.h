#ifndef g1_H
#define g1_H

/*
 * Header File for Driver:
 *
 * Alias: "g1" 
 * Type: "gyro_l3gd20"
 *
 * Generated from C source file with Python
 *
 * Built with BREAD
 */

#include "hal.h"

struct g1_namespace {
    bool (*init)();
    float (*read_x)();
    float (*read_y)();
    float (*read_z)();
};

extern struct g1_namespace const g1;

#endif /* g1_H */

#ifndef humidity1_H
#define humidity1_H

/*
 * Header File for Driver:
 *
 * Alias: "humidity1" 
 * Type: "humid_hdc1080"
 *
 * Generated from C source file with Python
 *
 * Built with BREAD
 */

#include "hal.h"

struct humidity1_namespace {
    bool (*init)();
    float (*read)();
};

extern struct humidity1_namespace const humidity1;

#endif /* humidity1_H */

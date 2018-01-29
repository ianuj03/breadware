#ifndef mic1_H
#define mic1_H

/*
 * Header File for Driver:
 *
 * Alias: "mic1" 
 * Type: "mic_max4466"
 *
 * Generated from C source file with Python
 *
 * Built with BREAD
 */

#include "hal.h"

struct mic1_namespace {
    bool (*init)();
    uint16_t (*read)();
};

extern struct mic1_namespace const mic1;

#endif /* mic1_H */

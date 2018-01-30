#ifndef speaker1_H
#define speaker1_H

/*
 * Header File for Driver:
 *
 * Alias: "speaker1" 
 * Type: "speaker"
 *
 * Generated from C source file with Python
 *
 * Built with BREAD
 */

#include "hal.h"

struct speaker1_namespace {
    bool (*init)();
    void (*write)(int);
};

extern struct speaker1_namespace const speaker1;

#endif /* speaker1_H */

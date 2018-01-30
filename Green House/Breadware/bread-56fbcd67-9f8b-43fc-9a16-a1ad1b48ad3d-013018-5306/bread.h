#ifndef BREAD_H
#define BREAD_H

/* include HAL layer */
#include "hal.h"

/* include drivers */
#include "temp1.h"
#include "humidity1.h"
#include "ldr1.h"
#include "speaker1.h"
#include "led1.h"
#include "button1.h"

bool bread_init();

#endif /* BREAD_H */
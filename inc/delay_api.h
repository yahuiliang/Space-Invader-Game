/*
 * CE2812 - 021
 * Winter 2016
 * Name: Yahui Liang
 */

#ifndef DELAY_API_H_
#define DELAY_API_H_

/* header file */
#include <inttypes.h>

/* SYSTICK structure */
typedef struct {
    uint32_t STK_CTRL;
    uint32_t STK_LOAD;
    uint32_t STK_VAL;
    const uint32_t CALIB;
} SYSTICK;

/* all symbolic numbers */
#define F_CPU 16000000UL
#define SYSTICK_BASE 0xE000E010

/* public method prototypes */

/**
 * Delays the number of milliseconds.
 * Args:
 * theDelay: the number of ms which needs to be delayed.
 */
void delay_ms(uint32_t);

/**
 * Delays the number of microseconds.
 * Args:
 * theDelay: the number of us which needs to be delayed.
 */
void delay_us(uint32_t);

#endif /* DELAY_API_H_ */

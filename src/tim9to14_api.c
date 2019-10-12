/*
 * CE2812 - 021
 * Winter 2016
 * Name: Yahui Liang
 */

#include "tim9to14_api.h"
#include <inttypes.h>

volatile static uint32_t* apb2enr = (uint32_t*) RCC_APB2ENR; // the register for configuring timers' clocks.
volatile static TIMER9to14* timer; // the timers which is manipulated by api methods from this file.

/**
 * Sets the pointer for timers from 9 to 14.
 */
void set_timer9to14_pointer(uint32_t timer_base) {
    timer = (TIMER9to14*) timer_base;
}

/**
 * Enable the clock for timer 9.
 */
void init_timer9() {
    *apb2enr |= 1 << TIM9_EN;
}

/**
 * Sets the ARR value in timer 9to14.
 * Args:
 * ticks: the number of ticks that ARR needs to be.
 */
void set_arr_timer9to14(uint32_t ticks) {
    timer->ARR = ticks;
}

/**
 * Sets the PSC value in timer 9to14.
 * Args:
 * ticks: the number of ticks that PSC needs to be.
 */
void set_psc_timer9to14(uint32_t ticks) {
    timer->PSC = ticks;
}

/**
 * Sets the timer into counter mode.
 */
void set_to_counter_mode_timer9to14() {
    timer->DIER |= 1 << UIE;
    timer->CR1 |= 1 << URS;
}

/**
 * Logs timer9's interrupt into NVIC register.
 */
void log_tim9_interrupt() {
    volatile uint32_t* iser0 = (uint32_t*) ISER0;
    *iser0 |= 1 << TIM9_INTERRUPT;
}

/**
 * Clears the pending flag for the interrupt.
 */
void clear_pending_flag_timer9to14() {
    timer->SR &= ~(1 << UIF);
}

/**
 * Starts the counter.
 */
void start_counter_timer9to14() {
    timer->CR1 |= 1 << CEN;
}

/**
 * Stops the counter.
 */
void stop_counter_timer9to14() {
    timer->CR1 &= ~(1 << CEN);
}

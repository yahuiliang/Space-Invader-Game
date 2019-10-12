/*
 * CE2812 - 021
 * Winter 2016
 * Lab 6 - Play a Tune
 * Name: Yahui Liang
 * Created: 01/21/2017
 */

/* All included header files */
#include <inttypes.h>
#include "tim2to5_api.h"

// private global variables.
volatile static uint32_t* apb1enr = (uint32_t*) RCC_APB1ENR; // the register for configuring timers' clocks.
volatile static TIMER2to5* timer; // the pointer points to a timer.

/**
 * Sets the internal timer pointer.
 * Args:
 * timer_base: the base address of the timer.
 */
void set_timer_pointer(uint32_t timer_base) {
    timer = (TIMER2to5*) timer_base;
}

/**
 * Configure the clock for the timer 3.
 */
void init_timer3() {
    *apb1enr |= 1 << 1; // enable the timer.
}

/**
 * Configure the clock for the timer 2.
 */
void init_timer2() {
    *apb1enr |= 1 << 0; // enable the timer.
}

/**
 * Configure the clock for the timer4.
 */
void init_timer4() {
    *apb1enr |= 1 << 2; // enable the timer.
}

/**
 * Configure the clock for the timer5.
 */
void init_timer5() {
    *apb1enr |= 1 << 3; // enable the timer.
}

/**
 * Sets the value in CCR1.
 * Args:
 * ticks: the number of ticks needs to be set in CCR1.
 */
void set_ccr1(uint32_t ticks) {
    timer->CCR1 = ticks;
}

/**
 * Sets the value in ARR.
 * Args:
 * ticks: the number of ticks needs to be set in ARR.
 */
void set_arr(uint32_t ticks) {
    timer->ARR = ticks;
}

/**
 * Sets the value in PSC.
 * Args:
 * ticks: the number of ticks needs to be set in PSC.
 */
void set_psc(uint32_t ticks) {
    timer->PSC = ticks;
}

/**
 * Sets the timer into output compare mode.
 */
void set_to_output_cmp_mode() {
    timer->CCMR1 &= ~(0b111 << OC1M);
    timer->CCMR1 |= 0b011 << OC1M;
}

/**
 * Sets the timer into output compare mode with interrupt.
 */
void set_to_output_cmp_mode_with_interrupt() {
    timer->CCMR1 &= ~(0b111 << OC1M);
    timer->CCMR1 |= 0b011 << OC1M;
    timer->DIER |= 1 << CC1IE;
    timer->DIER |= 1 << UIE;
}

/**
 * Sets the timer into encoder interface mode.
 */
void set_to_encoder_interface_mode() {
    timer->SMCR |= ENCODER_MODE3;
    // configure channels.
    timer->CCMR1 &= ~(0b11 << CC1S);
    timer->CCMR1 |= 1 << CC1S;
    timer->CCMR1 &= ~(0b11 << CC2S);
    timer->CCMR1 |= 1 << CC2S;
    // sets the polarity
    timer->CCER &= ~(1 << CC1P);
    timer->CCER &= ~(1 << CC2P);
}

/**
 * Sets the timer into general counter mode.
 */
void set_to_counter_mode() {
    timer->DIER |= 1 << UIE;
    timer->CR1 |= 1 << URS;
}

/**
 * Log timer 2's interrupt into NVIC.
 */
void log_tim2_interrupt() {
    volatile uint32_t* iser0 = (uint32_t*) ISER0;
    *iser0 |= 1 << TIM2_INTERRUPT;
}

/**
 * Log timer 3's interrupt into NVIC.
 */
void log_tim3_interrupt() {
    volatile uint32_t* iser0 = (uint32_t*) ISER0;
    *iser0 |= 1 << TIM3_INTERRUPT;
}

/**
 * Log timer 4's interrupt into NVIC.
 */
void log_tim4_interrupt() {
    volatile uint32_t* iser0 = (uint32_t*) ISER0;
    *iser0 |= 1 << TIM4_INTERRUPT;
}

/**
 * Log timer 5's interrupt into NVIC.
 */
void log_tim5_interrupt() {
    volatile uint32_t* iser1 = (uint32_t*) ISER1;
    *iser1 |= 1 << TIM5_INTERRUPT;
}

/**
 * Enables the output of the timer.
 */
void enable_output() {
    timer->CCER |= 1;
}

/**
 * Disable the output of the timer.
 */
void disable_output() {
    timer->CCER &= ~1;
}

/**
 * Starts counting.
 */
void start_counter() {
    timer->CR1 |= 1 << CEN;
}

/**
 * Stops counting.
 */
void stop_counter() {
    timer->CR1 &= ~1 << CEN;
}

/**
 * Clears the pending flag for the interruptive event.
 */
void clear_pending_flag() {
    timer->SR &= ~(1 << UIF);
}

/**
 * Enables the update event interrupt.
 */
void enable_update_event_interrupt() {
    timer->DIER |= 1 << UIE;
}

/**
 * Disables the update event interrupt.
 */
void disable_update_event_interrupt() {
    timer->DIER &= ~(1 << UIE);
}

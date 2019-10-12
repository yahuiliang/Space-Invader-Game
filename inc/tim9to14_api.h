/*
 * CE2812 - 021
 * Winter 2016
 * Name: Yahui Liang
 */

#include <inttypes.h>

#define RCC_APB1ENR 0x40023840
#define RCC_APB2ENR 0x40023844
#define TIM9_BASE 0x40014000
#define ISER0 0xE000E100
#define ISER1 0xE000E104

/* The structure for TIMER9 to 14 */
typedef struct {
    uint32_t CR1;
    uint32_t reserved1;
    uint32_t SMCR;
    uint32_t DIER;
    uint32_t SR;
    uint32_t EGR;
    uint32_t CCMR1;
    uint32_t reserved2;
    uint32_t CCER;
    uint32_t CNT;
    uint32_t PSC;
    uint32_t ARR;
    uint32_t reserved3;
    uint32_t CCR1;
    uint32_t CCR2;
} TIMER9to14;

/* APB2ENR bits */
#define TIM9_EN 16
/* SR bits */
#define UIF 0
/* DIER bits */
#define UIE 0
#define CC1IE 1
/* CR1 bits */
#define CEN 0
#define URS 2
/* NVIC bits */
#define TIM9_INTERRUPT 24

/**
 * Sets the pointer for timers from 9 to 14.
 */
void set_timer9to14_pointer(uint32_t timer_base);

/**
 * Enable the clock for timer 9.
 */
void init_timer9();

/**
 * Sets the ARR value in timer 9to14.
 * Args:
 * ticks: the number of ticks that ARR needs to be.
 */
void set_arr_timer9to14(uint32_t ticks);

/**
 * Sets the PSC value in timer 9to14.
 * Args:
 * ticks: the number of ticks that PSC needs to be.
 */
void set_psc_timer9to14(uint32_t ticks);

/**
 * Sets the timer into counter mode.
 */
void set_to_counter_mode_timer9to14();

/**
 * Logs timer9's interrupt into NVIC register.
 */
void log_tim9_interrupt();

/**
 * Starts the counter.
 */
void start_counter_timer9to14();

/**
 * Stops the counter.
 */
void stop_counter_timer9to14();

/**
 * Clears the pending flag for the interrupt.
 */
void clear_pending_flag_timer9to14();

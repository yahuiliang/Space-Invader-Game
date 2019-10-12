/*
 * CE2812 - 021
 * Winter 2016
 * Name: Yahui Liang
 */

#ifndef TIM2TO5_API_H_
#define TIM2TO5_API_H_

#define RCC_APB1ENR 0x40023840
#define ISER0 0xE000E100
#define ISER1 0xE000E104
#define TIM2_BASE 0x40000000
#define TIM3_BASE 0x40000400
#define TIM4_BASE 0x40000800
#define TIM5_BASE 0x40000C00

/* The structure for TIMER2 to 5 */
typedef struct {
    uint32_t CR1;
    uint32_t CR2;
    uint32_t SMCR;
    uint32_t DIER;
    uint32_t SR;
    uint32_t EGR;
    uint32_t CCMR1;
    uint32_t CCMR2;
    uint32_t CCER;
    uint32_t CNT;
    uint32_t PSC;
    uint32_t ARR;
    uint32_t reserved1;
    uint32_t CCR1;
    uint32_t CCR2;
    uint32_t CCR3;
    uint32_t CCR4;
    uint32_t reserved2;
    uint32_t DCR;
    uint32_t DMAR;
} TIMER2to5;

/* CCER bits */
#define CC1P 1
#define CC2P 5
/* CCMR1 bits */
#define CC1S 0
#define CC2S 8
#define OC1M 4
/* CR1 bits */
#define CEN 0
#define URS 2
/* SMCR modes */
#define ENCODER_MODE1 1
#define ENCODER_MODE2 2
#define ENCODER_MODE3 3
/* DIER bits */
#define UIE 0
#define CC1IE 1
/* ISER0 bits */
#define TIM2_INTERRUPT 28
#define TIM3_INTERRUPT 29
#define TIM4_INTERRUPT 30
#define TIM5_INTERRUPT 18
/* SR bits */
#define UIF 0

/**
 * Sets the internal timer pointer.
 * Args:
 * timer_base: the base address of the timer.
 */
void set_timer_pointer(uint32_t);

/**
 * Configure the clock for the timer 3.
 */
void init_timer3();

/**
 * Configure the clock for the timer 2.
 */
void init_timer2();

/**
 * Configure the clock for the timer4.
 */
void init_timer4();

/**
 * Configure the clock for the timer5.
 */
void init_timer5();

/**
 * Sets the value in CCR1.
 * Args:
 * ticks: the number of ticks needs to be set in CCR1.
 */
void set_ccr1(uint32_t);

/**
 * Sets the value in ARR.
 * Args:
 * ticks: the number of ticks needs to be set in ARR.
 */
void set_arr(uint32_t);

/**
 * Sets the value in PSC.
 * Args:
 * ticks: the number of ticks needs to be set in PSC.
 */
void set_psc(uint32_t);

/**
 * Sets the timer into output compare mode.
 */
void set_to_output_cmp_mode();

/**
 * Sets the time into encoder interface mode.
 */
void set_to_encoder_interface_mode();

/**
 * Sets the timer into general counter mode.
 */
void set_to_counter_mode();

/**
 * Log timer 2's interrupt into NVIC.
 */
void log_tim2_interrupt();

/**
 * Log timer 3's interrupt into NVIC.
 */
void log_tim3_interrupt();

/**
 * Log timer 4's interrupt into NVIC.
 */
void log_tim4_interrupt();

/**
 * Log timer 5's interrupt into NVIC.
 */
void log_tim5_interrupt();

/**
 * Starts counting.
 */
void start_counter();

/**
 * Stops counting.
 */
void stop_counter();

/**
 * Enables the output of the timer.
 */
void enable_output();

/**
 * Disable the output of the timer.
 */
void disable_output();

/**
 * Clears the pending flag for the interruptive event.
 */
void clear_pending_flag();

/**
 * Enables the update event interrupt.
 */
void enable_update_event_interrupt();

/**
 * Disables the update event interrupt.
 */
void disable_update_event_interrupt();

#endif /* TIM2TO5_API_H_ */

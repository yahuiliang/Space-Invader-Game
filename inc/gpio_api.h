/*
 * CE2812 - 021
 * Winter 2016
 * Name: Yahui Liang
 */

#ifndef GPIO_API_H_
#define GPIO_API_H_

#include <inttypes.h>

#define RCC_AHB1ENR 0x40023830
#define GPIOA_BASE 0x40020000
#define GPIOB_BASE 0x40020400

/* GPIO structure */
typedef struct {
    uint32_t MODER;
    uint32_t OTYPER;
    uint32_t OSPEEDR;
    uint32_t PUPDR;
    uint32_t IDR;
    uint32_t ODR;
    uint32_t BSRR;
    uint32_t LCKR;
    uint32_t AFRL;
    uint32_t AFRH;
} GPIOx;

/**
 * Links the private pointer with the provided address.
 * Args:
 * gpio_base: the gpio port needs to be manipulated with.
 */
void set_gpio_pointer(uint32_t);

/**
 * Enable the clock for that GPIO port.
 * Args:
 * port: 0 represents A.
 *       1 represents B, etc.
 */
void init_gpiox(uint32_t port);

/**
 * Sets a pin into input mode.
 * Args:
 * pin: the pin needs to be set.
 */
void set_to_input_mode(uint8_t);

/**
 * Sets a pin into output mode.
 * Args:
 * pin: the pin needs to be set.
 */
void set_to_output_mode(uint8_t);

/**
 * Sets a pin into alternate function mode.
 * Args:
 * pin: the pin needs to be set.
 */
void set_to_alt_func_mode(uint8_t);

/**
 * Sets a pin into analog mode.
 * Args:
 * pin: the pin needs to be set.
 */
void set_to_analog_mode(uint8_t);

/**
 * Sets a pin's alternate function.
 * Args:
 * pin: the pin needs to be set.
 * value: the function that the pin needs to perform.
 */
void set_alt_function(uint8_t, uint8_t);

#endif /* GPIO_API_H_ */

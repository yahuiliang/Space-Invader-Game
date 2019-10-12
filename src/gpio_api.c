/*
 * CE2812 - 021
 * Winter 2016
 * Lab 6 - Play a Tune
 * Name: Yahui Liang
 * Created: 01/21/2017
 */

/* All included header files */
#include "gpio_api.h"
#include <inttypes.h>

/**
 * Sets a mode for a pin.
 * Args:
 * value: the mode of the pin.
 * pin: the pin needs to be set.
 */
static void set_mode(uint8_t, uint8_t);

volatile static GPIOx* gpiox; // the pointer points to a specific GPIO base register(MODER).

/**
 * Links the private pointer with the provided address.
 * Args:
 * gpio_base: the gpio port needs to be manipulated with.
 */
void set_gpio_pointer(uint32_t gpio_base) {
    gpiox = (GPIOx*) gpio_base;
}

/**
 * Enable the clock for that GPIO port.
 * Args:
 * port: 0 represents A.
 *       1 represents B, etc.
 */
void init_gpiox(uint32_t port) {
    volatile uint32_t* ahb1enr = (uint32_t*) RCC_AHB1ENR;
    *ahb1enr |= 1 << port;
}

/**
 * Sets a pin into input mode.
 * Args:
 * pin: the pin needs to be set.
 */
void set_to_input_mode(uint8_t pin) {
    set_mode(0b00, pin);
}

/**
 * Sets a pin into output mode.
 * Args:
 * pin: the pin needs to be set.
 */
void set_to_output_mode(uint8_t pin) {
    set_mode(0b01, pin);
}

/**
 * Sets a pin into alternate function mode.
 * Args:
 * pin: the pin needs to be set.
 */
void set_to_alt_func_mode(uint8_t pin) {
    set_mode(0b10, pin);
}

/**
 * Sets a pin into analog mode.
 * Args:
 * pin: the pin needs to be set.
 */
void set_to_analog_mode(uint8_t pin) {
    set_mode(0b11, pin);
}

/**
 * Sets a pin's alternate function.
 * Args:
 * pin: the pin needs to be set.
 * value: the function that the pin needs to perform.
 */
void set_alt_function(uint8_t pin, uint8_t value) {
    if (pin <= 7) {
        gpiox->AFRL &= ~(0b1111 << (pin * 4));
        gpiox->AFRL |= value << (pin * 4);
    } else {
        gpiox->AFRH &= ~(0b1111 << ((pin - 8) * 4));
        gpiox->AFRH |= value << ((pin - 8) * 4);
    }
}

/**
 * Sets a mode for a pin.
 * Args:
 * value: the mode of the pin.
 * pin: the pin needs to be set.
 */
void static set_mode(uint8_t value, uint8_t pin) {
    gpiox->MODER &= ~(0b11 << (pin * 2));
    gpiox->MODER |= value << (pin * 2);
}


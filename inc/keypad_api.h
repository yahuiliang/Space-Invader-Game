/*
 * CE2812 - 021
 * Winter 2016
 * Name: Yahui Liang
 */

#ifndef KEYPAD_API_H_
#define KEYPAD_API_H_

#define RCC_AHB1ENR 0x40023830
#define GPIOC_BASE 0x40020800

/**
 * Enable the clock for GPIOC, and pull up rows.
 */
void key_init();

/**
 * Returns the value of the key which is pressed. If no key is
 * pressed, 0 will be returned.
 */
int key_getkey_noblock();

/**
 * Returns the value of the key which is pressed. However, the method blocks if no key is
 * pressed.
 */
int key_getkey();

/**
 * The method returns the character of the key which is pressed.
 */
char key_getchar();

#endif /* KEYPAD_API_H_ */

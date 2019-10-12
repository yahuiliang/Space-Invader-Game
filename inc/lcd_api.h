/*
 * CE2812 - 021
 * Winter 2016
 * Name: Yahui Liang
 */

#ifndef LCD_API_H_
#define LCD_API_H_

/* header file */
#include "inttypes.h"

/* register base addresses */
#define RCC_AHB1ENR 0x40023830
#define GPIOB_BASE 0x40020400
#define GPIOC_BASE 0x40020800

/* All register or bits offset */
#define Px0 0
#define Px1 1
#define Px2 2
#define Px3 3

/* useful logic */
#define GPIOBEN 1 << 1
#define GPIOCEN 1 << 2
#define SET 1
#define OUTPUT 1
#define RS_SET 1 << 0
#define RW_SET 1 << 1
#define RS_CLR 1 << (0 + 16)
#define RW_CLR 1 << (1 + 16)
#define E_SET 1 << 2
#define E_CLR 1 << (2 + 16)

/* public method prototypes */

/**
 * Initializes the lcd.
 */
void lcd_init();

/**
 * Clears all contents on the lcd.
 */
void lcd_clear();

/**
 * Returns the cursor to the home position.
 */
void lcd_home();

void lcd_data(uint8_t);

/**
 * Sets the CGRAM position.
 * Args:
 * addr: the address where the character needs to be stored.
 */
void lcd_set_cgram_position(uint8_t);

/**
 * Sets the cursor position.
 * Args:
 * row: 0 is the first row, and 1 is the second row.
 * col: 0 is the first col, and 15 is the last col.
 */
void lcd_set_position(uint8_t, uint8_t);

/**
 * Prints a string on lcd.
 * Args:
 * string: the string which needs to be displayed.
 */
int lcd_print_string(char[]);

/**
 * Prints a number on lcd.
 * Args:
 * num: the number which needs to be displayed.
 */
void lcd_print_num(int);

#endif /* LCD_API_H_ */

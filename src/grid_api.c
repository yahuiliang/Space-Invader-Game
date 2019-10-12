/*
 * CE2812 - 021
 * Winter 2016
 * Name: Yahui Liang
 */

#include "grid_api.h"
#include "lcd_api.h"
#include "tim2to5_api.h"
#include <inttypes.h>

static uint8_t player[] = {0b11000, 0b11000, 0b11100, 0b11111, 0b11111, 0b11100, 0b11000, 0b11000};
static uint8_t enemy[] = {0b00111, 0b00100, 0b00100, 0b11100, 0b11100, 0b00100, 0b00100, 0b00111};
static uint8_t bullet[] = {0b00000, 0b00000, 0b00000, 0b11111, 0b11111, 0b00000, 0b00000, 0b00000};
static int isDied = 0;
static int score = 0;

/**
 * Initializes the row0.
 * Args:
 * row0: the pointer where the array should be started.
 */
void init_row0(volatile Grid* row0) {
    for (int i = 0; i < COLS; i++) {
        Grid grid = {0, i, 0, 0, 0};
        row0[i] = grid;
    }
}

/**
 * Initializes the row1.
 * Args:
 * row1: the pointer where the array should be started.
 */
void init_row1(volatile Grid* row1) {
    for (int i = 0; i < COLS; i++) {
        Grid grid = {1, i, 0, 0, 0};
        row1[i] = grid;
    }
}

/**
 * Prints one grid based on the state of the grid.
 * Also, the method does some relative actions when certain
 * events occur.
 * Args:
 * grid_pointer: the reference of the grid.
 */
void print_grid(volatile Grid* grid_pointer) {
    Grid grid = *grid_pointer;
    if (!grid.hasPlayer && !grid.hasEnemy && !grid.hasBullet) {
        // nothing in the grid results in nothing appears.
        lcd_set_position(grid.row, grid.col);
        lcd_data(' ');
        grid.hasBullet = 0;
        grid.hasEnemy = 0;
        grid.hasPlayer = 0;
    } else if (grid.hasPlayer && grid.hasEnemy) {
        // player and enemies in the same grid results in losing the game,
        // and both player and enemies disappear.
        lcd_set_position(grid.row, grid.col);
        lcd_data(' ');
        grid.hasBullet = 0;
        grid.hasEnemy = 0;
        grid.hasPlayer = 0;
        isDied = 1;
    } else if (grid.hasBullet && grid.hasEnemy) {
        // bullet can attack enemies.
        lcd_set_position(grid.row, grid.col);
        lcd_data(' ');
        grid.hasBullet = 0;
        grid.hasEnemy = 0;
        grid.hasPlayer = 0;
        score++;
    } else if (grid.hasBullet) {
        // prints bullet if only bullet is in the grid.
        lcd_set_position(grid.row, grid.col);
        lcd_data(BULLET);
    } else if (grid.hasPlayer) {
        // prints player if only player is in the grid.
        lcd_set_position(grid.row, grid.col);
        lcd_data(PLAYER);
    } else if (grid.hasEnemy) {
        // prints enemy if only enemy is in the grid.
        lcd_set_position(grid.row, grid.col);
        lcd_data(ENEMY);
    }
    *grid_pointer = grid; // store the status back to the grid.
}

/**
 * Initializes all graphics used in this program.
 */
void init_graphics() {
    lcd_set_cgram_position(0);
    for (int i = 0; i < SIZE; i++) {
        lcd_data(player[i]);
    }
    for (int i = 0; i < SIZE; i++) {
        lcd_data(enemy[i]);
    }
    for (int i = 0; i < SIZE; i++) {
        lcd_data(bullet[i]);
    }
}

/**
 * Update all grids on lcd.
 * Args:
 * row0: grids at row0.
 * row1: grids at row1.
 */
void update_grids(volatile Grid* row0, volatile Grid* row1) {
    for (int i = 0; i < COLS; i++) {
        print_grid(&row0[i]);
        print_grid(&row1[i]);
    }
}

/**
 * Check if the player has died.
 */
int is_player_died() {
    return isDied;
}

/**
 * Gets the score that the player gets.
 */
int get_score() {
    return score;
}

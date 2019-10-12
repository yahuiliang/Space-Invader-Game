/*
 * CE2812 - 021
 * Winter 2016
 * Name: Yahui Liang
 */

#ifndef GRID_API_H_
#define GRID_API_H_

#define SIZE 8
#define COLS 16
#define PLAYER 0
#define ENEMY 1
#define BULLET 2

typedef struct {
    int row;
    int col;
    int hasPlayer;
    int hasBullet;
    int hasEnemy;
} Grid;

/**
 * Initializes all graphics used in this program.
 */
void init_graphics();

/**
 * Initializes the row0.
 * Args:
 * row0: the pointer where the array should be started.
 */
void init_row0(volatile Grid* row0);

/**
 * Initializes the row1.
 * Args:
 * row1: the pointer where the array should be started.
 */
void init_row1(volatile Grid* row1);

/**
 * Prints one grid based on the state of the grid.
 * Also, the method does some relative actions when certain
 * events occur.
 * Args:
 * grid_pointer: the reference of the grid.
 */
void print_grid(volatile Grid* grid_pointer);

/**
 * Update all grids on lcd.
 * Args:
 * row0: grids at row0.
 * row1: grids at row1.
 */
void update_grids(volatile Grid* row0, volatile Grid* row1);

/**
 * Check if the player has died.
 */
int is_player_died();

/**
 * Gets the score that the player gets.
 */
int get_score();

#endif /* GRID_API_H_ */

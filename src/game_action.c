/*
 * CE2812 - 021
 * Winter 2016
 * Name: Yahui Liang
 */

#include "grid_api.h"
#include "game_action.h"
#include <stdlib.h>

/**
 * Moves up the player.
 * Args:
 * row0: the array where row 0 grids are stored.
 * row1: the array where row 1 grids are stored.
 */
void move_up_player(volatile Grid* row0, volatile Grid* row1) {
    row0[0].hasPlayer = 1;
    row1[0].hasPlayer = 0;
}

/**
 * Moves down the player.
 * Args:
 * row0: the array where row 0 grids are stored.
 * row1: the array where row 1 grids are stored.
 */
void move_down_player(volatile Grid* row0, volatile Grid* row1) {
    row0[0].hasPlayer = 0;
    row1[0].hasPlayer = 1;
}

/**
 * Moves bullets for distance 1 to the right of the LCD.
 * Args:
 * row0: the array where row 0 grids are stored.
 * row1: the array where row 1 grids are stored.
 */
void move_bullets(volatile Grid* row0, volatile Grid* row1) {
    Grid temp_row0[COLS];
    Grid temp_row1[COLS];

    // copy elements to temp arrays.
    for (int i = 0; i < COLS; i++) {
        temp_row0[i] = row0[i];
        temp_row1[i] = row1[i];
    }

    // repeat increase bullets' positions by one.
    // set the current grid's hasBullet status to 0.
    // and set the next grid's hasBullet status to 1.
    for (int i = 0; i < COLS; i++) {
        if (temp_row0[i].hasBullet) {
            if (i != COLS - 1 ) {
                row0[i + 1].hasBullet = 1;
            }
            row0[i].hasBullet = 0;
        }
        if (temp_row1[i].hasBullet) {
            if (i != COLS - 1) {
                row1[i + 1].hasBullet = 1;
            }
            row1[i].hasBullet = 0;
        }
    }
}

/**
 * Moves enemies for distance 1 to the left of the LCD.
 * Args:
 * row0: the array where row 0 grids are stored.
 * row1: the array where row 1 grids are stored.
 */
void move_enemies(volatile Grid* row0, volatile Grid* row1) {
    Grid temp_row0[COLS];
    Grid temp_row1[COLS];

    // copy elements to temp arrays.
    for (int i = 0; i < COLS; i++) {
        temp_row0[i] = row0[i];
        temp_row1[i] = row1[i];
    }

    // repeat increase enemies' positions by one.
    // set the current grid's hasEnemy status to 0.
    // and set the next grid's hasEnemy status to 1.
    for (int i = 0; i < COLS; i++) {
        if (temp_row0[i].hasEnemy) {
            if (i != 0) {
                row0[i - 1].hasEnemy = 1;
            }
            row0[i].hasEnemy = 0;
        }
        if (temp_row1[i].hasEnemy) {
            if (i != 0) {
                row1[i - 1].hasEnemy = 1;
            }
            row1[i].hasEnemy = 0;
        }
    }
}

/*
 * CE2812 - 021
 * Winter 2016
 * Name: Yahui Liang
 */

#ifndef GAME_ACTION_H_
#define GAME_ACTION_H_

/**
 * Moves up the player.
 * Args:
 * row0: the array where row 0 grids are stored.
 * row1: the array where row 1 grids are stored.
 */
void move_up_player(volatile Grid* row0, volatile Grid* row1);

/**
 * Moves down the player.
 * Args:
 * row0: the array where row 0 grids are stored.
 * row1: the array where row 1 grids are stored.
 */
void move_down_player(volatile Grid* row0, volatile Grid* row1);

/**
 * Moves bullets for distance 1 to the right of the LCD.
 * Args:
 * row0: the array where row 0 grids are stored.
 * row1: the array where row 1 grids are stored.
 */
void move_bullets(volatile Grid* row0, volatile Grid* row1);

/**
 * Moves enemies for distance 1 to the left of the LCD.
 * Args:
 * row0: the array where row 0 grids are stored.
 * row1: the array where row 1 grids are stored.
 */
void move_enemies(volatile Grid* row0, volatile Grid* row1);

#endif /* GAME_ACTION_H_ */

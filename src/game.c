/*
 * CE2812 - 021
 * Winter 2016
 * Name: Yahui Liang
 */

#include "lcd_api.h"
#include "grid_api.h"
#include "game_action.h"
#include "delay_api.h"
#include "tim2to5_api.h"
#include "tim9to14_api.h"
#include "keypad_api.h"
#include "game.h"
#include "tune_generator.h"
#include <stdlib.h>

static volatile Grid* row0;
static volatile Grid* row1;

/**
 * The program is a space invader game with background music playing.
 * Player can be moved in the first column. Enemies are created at last
 * column. The player can also shot moving enemies.
 *
 * Thoughts about this project:
 * In this project, the main algorithm is in game_action.c. The idea for moving the player, enemies, and
 * bullets is creating a structure which represents a grid. In the grid structure, I have
 * hasBullet, hasPlayer, and hasEnemy to show the status of one grid. Move methods in game_action.c file
 * actually update these variables for different grids, and this looks like a state machine (update states).
 * Also, the print_grid method in grid_api.c file can print out one grid based on the grid's status. Update_grids method
 * in that file loops through all grids and print out characters for all of them. Moving actions of enemies and bullets
 * are completed in TIM2,4. In these timer's interruptive subroutines, each grid's status gets updated. In the main,
 * update_grids method is called over and over again in order to refresh the lcd all the time. Polling for keypad is for moving
 * the player. The most interesting thing in this program is the background music, and the program looks like a multiple threads program because
 * of this. However, there is not a real thread created for playing the music. Instead, I used the TIM interruptive subroutine to achieve this.
 * TIM9 (causes interrupt) is used for controlling the duration of the sound, and TIM3 is used for making different notes. Since the interruptive subroutine
 * can be finished in a very fast speed, it gives us a feeling that it plays simultaneously while the game is running. One issue that i meet
 * in my program is that values in row0 and row1 can be changed without using 'volatile' when the program is running. I know this
 * may be caused by the optimizer. However, I did not turn on any optimizers, so this makes no sense. However, I decided to try it, and it
 * fixed the problem. I got no idea how it fixed that problem.
 */
int main(void) {
    lcd_init();
    key_init();
    init_tune_generator();
    init_graphics();
    row0 = calloc(16, sizeof(Grid));
    row1 = calloc(16, sizeof(Grid));
    init_row0(row0);
    init_row1(row1);

    // initiate the player.
    row0[0].hasPlayer = 1;
    print_grid(&row0[0]);

    init_timer2(); // the timer for moving enemies.
    init_timer5(); // the timer for creating enemies.
    init_timer4(); // the timer for moving bullets.

    // sets up the counter for moving enemies.
    set_timer_pointer(TIM2_BASE);
    set_to_counter_mode();
    set_psc(1000); // sets the counter's speed to 10Hz.
    set_arr(16000);
    log_tim2_interrupt(); // sets NVIC.
    start_counter();

    // sets up the counter for creating enemies.
    set_timer_pointer(TIM5_BASE);
    set_to_counter_mode();
    set_psc(1000);
    set_arr(32000);
    log_tim5_interrupt(); // sets NVIC.
    start_counter();

    // sets up the counter for shooting bullets.
    set_timer_pointer(TIM4_BASE);
    set_to_counter_mode();
    set_psc(1000);
    set_arr(8000);
    log_tim4_interrupt(); // sets NVIC
    start_counter();

    play_song();

    // repeat updating LCD and getting key press event.
    // perform different functions for different keys.
    while (!is_player_died()) {
        update_grids(row0, row1);
        int key_code = key_getkey_noblock();
        if (key_code == 2) {
            move_up_player(row0, row1);
        } else if (key_code == 10) {
            move_down_player(row0, row1);
        } else if (key_code == 6) {
            // generate a bullet.
            if (row0[0].hasPlayer) {
                row0[1].hasBullet = 1;
            } else if (row1[0].hasPlayer) {
                row1[1].hasBullet = 1;
            }
        }
    }
    // stop updating lcd.
    set_timer_pointer(TIM2_BASE);
    disable_update_event_interrupt();
    set_timer_pointer(TIM5_BASE);
    disable_update_event_interrupt();
    set_timer_pointer(TIM4_BASE);
    disable_update_event_interrupt();

    // print lose message.
    lcd_clear();
    lcd_home();
    lcd_print_string("YOU LOSE!");
    // print score.
    int score = get_score();
    lcd_set_position(1, 0);
    lcd_print_string("SCORE:");
    lcd_print_num(score);
    // stop playing the song.
    stop_playing_song();
    while (1);
    return 0;
}

/**
 * Move all enemies every time it gets called.
 */
void TIM2_IRQHandler(void) {
    set_timer_pointer(TIM2_BASE);
    clear_pending_flag();
    move_enemies(row0, row1);
}

/**
 * Generates enemies every time it gets called.
 */
void TIM5_IRQHandler(void) {
    set_timer_pointer(TIM5_BASE);
    clear_pending_flag();
    // generate 1 or 0 for row 0 and row 1.
    // based on this random number in order to
    // determine whether create a enemy at the certain row.
    int random = rand();
    int row0_random = random % 2;
    random = rand();
    int row1_random = random % 2;
    if (row0_random && row1_random) {
        row0[15].hasEnemy = 1;
        row1[15].hasEnemy = 1;
    } else if (row0_random && !row1_random) {
        row0[15].hasEnemy = 1;
    } else {
        row1[15].hasEnemy = 1;
    }
    // Since the time delay for creating enemies is different
    // all the time, I also used the random value to set the timer's ARR.
    set_timer_pointer(TIM5_BASE);
    random = rand();
    int random_time = random % 32000 + 32000;
    set_arr(random_time);
}

/**
 * Move all bullets every time it gets called.
 */
void TIM4_IRQHandler(void) {
    set_timer_pointer(TIM4_BASE);
    clear_pending_flag();
    move_bullets(row0, row1);
}

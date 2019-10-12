/*
 * CE2812 - 021
 * Winter 2016
 * Lab 6 - Play a Tune
 * Name: Yahui Liang
 * Created: 01/21/2017
 */

/* All included header files */
#include "gpio_api.h"
#include "tim2to5_api.h"
#include <inttypes.h>
#include "tim2to5_api.h"
#include "delay_api.h"
#include "tune_generator.h"
#include "tim9to14_api.h"

/**
 * Initializes the tune generator. This method mainly configures the timer
 * and the correspond pin.
 */
void init_tune_generator() {
    init_timer3();
    init_timer9();
    init_gpiox(1); // initialize GPIOB

    set_gpio_pointer(GPIOB_BASE);
    set_to_alt_func_mode(4); // set pin4 to alternate function mode.
    set_alt_function(4, 2);

    set_timer_pointer(TIM3_BASE);
    set_to_output_cmp_mode();

    set_timer9to14_pointer(TIM9_BASE);
    set_to_counter_mode_timer9to14();
    set_psc_timer9to14(16000);
    set_arr_timer9to14(1);
    log_tim9_interrupt();
}

/**
 * The method can play a song.
 */
void play_song() {
    set_timer9to14_pointer(TIM9_BASE);
    start_counter_timer9to14();
}

/**
 * Stop playing the song.
 */
void stop_playing_song() {
    set_timer9to14_pointer(TIM9_BASE);
    stop_counter_timer9to14();
    set_timer_pointer(TIM3_BASE);
    disable_output();
    stop_counter();
}

/**
 * The interruptive subroutine for playing the background music.
 */
void TIM1_BRK_TIM9_IRQHandler(void) {
    set_timer9to14_pointer(TIM9_BASE);
    clear_pending_flag_timer9to14();
    const note section1[] = { { LA3, Q }, { LA3, Q }, { LA3, Q }, { F3, E + S },
            { C4, S }, { LA3, Q }, { F3, E + S }, { C4, S }, { LA3, H },
            { E4, Q }, { E4, Q }, { E4, Q }, { F4, E + S }, { C4, S },
            { Ab3, Q }, { F3, E + S }, { C4, S }, { LA3, H }, { LA4, Q }, { LA3,
            E + S }, { LA3, S }, { LA4, Q }, { Ab4, E + S }, { G4, S },
            { Gb4, S }, { E4, S }, { F4, E }, { 0, 0 } };
    const note section2[] = { { Bb3, E }, { Eb4, Q }, { D4, E + S }, { Db4, S },
            { C4, S }, { B3, S }, { C4, E }, { 0, 0 } };
    const note section3[] = { { F3, E }, { Ab3, Q }, { F3, E + S }, { LA3, S },
            { C4, Q }, { LA3, E + S }, { C4, S }, { E4, H }, { LA4, Q }, { LA3,
            E + S }, { LA3, S }, { LA4, Q }, { Ab4, E + S }, { G4, S },
            { Gb4, S }, { E4, S }, { F4, E }, { 0, 0 } };
    const note section4[] = { { Bb3, E }, { Eb4, Q }, { D4, E + S }, { Db4, S },
            { C4, S }, { B3, S }, { C4, E }, { 0, 0 } };
    const note section5[] = { { F3, E }, { Ab3, Q }, { F3, E + S }, { C4, S }, {
    LA3, Q }, { F3, E + S }, { C4, S }, { LA3, H }, { 0, 0 } };
    const note* sections[] = { &section1[0], &section2[0], &section3[0],
            &section4[0], &section5[0] };

    static int sectionIndex = 0;
    static int noteIndex = 0;

    const note* cur_section = sections[sectionIndex];
    note cur_note = cur_section[noteIndex];

    // determines if the end of the array is reached.
    if (cur_note.duration != 0 && cur_note.frequency != 0) {
        set_timer_pointer(TIM3_BASE);
        // sets the note.
        uint32_t arr_val = 16000000 / (2 * cur_note.frequency);
        set_ccr1(0);
        set_arr(arr_val);
        enable_output();
        start_counter();
        noteIndex++;

        // sets the duration.
        set_timer_pointer(TIM9_BASE);
        set_arr_timer9to14(cur_note.duration);
    } else {
        // jump to the next notes array.
        noteIndex = 0;
        sectionIndex++;
    }
    if (sectionIndex == 5) {
        // if in the new array, reset the section index into 0.
        sectionIndex = 0;
        set_timer_pointer(TIM3_BASE);
        disable_output();
        stop_counter();
        set_timer_pointer(TIM9_BASE);
        set_arr_timer9to14(E + 1);
    }
}

/*
 * CE2812 - 021
 * Winter 2016
 * Lab 6 - Play a Tune
 * Name: Yahui Liang
 * Created: 01/21/2017
 */

#ifndef TUNE_GENERATOR_H_
#define TUNE_GENERATOR_H_

/* The structure of a note */
typedef struct {
    uint32_t frequency;
    uint32_t duration;
} note;

// NB: ALL NOTES DEFINED WITH STANDARD ENGLISH NAMES, EXCEPT FROM "A"
// THAT IS CALLED WITH THE ITALIAN NAME "LA" BECAUSE A0,A1...ARE THE ANALOG PINS ON ARDUINO.
// (Ab IS CALLED Ab AND NOT LAb)
#define C0 16
#define Db0 17
#define D0  18
#define Eb0 19
#define E0  21
#define F0  22
#define Gb0 23
#define G0  25
#define Ab0 26
#define LA0 28
#define Bb0 29
#define B0  31
#define C1  33
#define Db1 35
#define D1  37
#define Eb1 39
#define E1  41
#define F1  44
#define Gb1 46
#define G1  49
#define Ab1 52
#define LA1 55
#define Bb1 58
#define B1  62
#define C2  65
#define Db2 69
#define D2  73
#define Eb2 78
#define E2  82
#define F2  87
#define Gb2 93
#define G2  98
#define Ab2 104
#define LA2 110
#define Bb2 117
#define B2  123
#define C3  131
#define Db3 139
#define D3  147
#define Eb3 156
#define E3  165
#define F3  175
#define Gb3 185
#define G3  196
#define Ab3 208
#define LA3 220
#define Bb3 233
#define B3  247
#define C4  262
#define Db4 277
#define D4  294
#define Eb4 311
#define E4  330
#define F4  349
#define Gb4 370
#define G4  392
#define Ab4 415
#define LA4 440
#define Bb4 466
#define B4  494
#define C5  523
#define Db5 554
#define D5  587
#define Eb5 622
#define E5  659
#define F5  698
#define Gb5 740
#define G5  784
#define Ab5 831
#define LA5 880
#define Bb5 932
#define B5  988
#define C6  1047
#define Db6 1109
#define D6  1175
#define Eb6 1245
#define E6  1319
#define F6  1397
#define Gb6 1480
#define G6  1568
#define Ab6 1661
#define LA6 1760
#define Bb6 1865
#define B6  1976
#define C7  2093
#define Db7 2217
#define D7  2349
#define Eb7 2489
#define E7  2637
#define F7  2794
#define Gb7 2960
#define G7  3136
#define Ab7 3322
#define LA7 3520
#define Bb7 3729
#define B7  3951
#define C8  4186
#define Db8 4435
#define D8  4699
#define Eb8 4978

// DURATION OF THE NOTES
#define BPM 120    //  you can change this value changing all the others
#define H 2*Q //half 2/4
#define Q 60000/BPM //quarter 1/4
#define E Q/2   //eighth 1/8
#define S Q/4 // sixteenth 1/16
#define W 4*Q // whole 4/4

/**
 * Initializes the tune generator. This method mainly configures the timer
 * and the correspond pin.
 */
void init_tune_generator();

/**
 * The method can play a song.
 */
void play_song();

/**
 * Stop playing the song.
 */
void stop_playing_song();

void TIM1_BRK_TIM9_IRQHandler(void);

#endif /* TUNE_GENERATOR_H_ */

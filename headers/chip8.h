#ifndef __CHIP8_H__
#define __CHIP8_H__
/*
 *@Chip-8 Machine 
 * */
#include "emulator.h"

enum State{ QUIT = 0, RUNNING, PAUSED};//PAUSED -> for debugging purposes 

struct Machine{
    enum State emulator_state;
};

static bool init_chip8(struct Machine *chip8);

extern struct Machine chip8;
#endif //__CHIP8_H__

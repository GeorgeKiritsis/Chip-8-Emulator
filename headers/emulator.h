#ifndef __EMULATOR_H__
#define __EMULATOR_H__

/*
 *@ Emulator ,Settings & helper functions
 */

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>

#include "chip8.h"

struct Emulator{
    SDL_Window      *window;
    SDL_Renderer    *renderer;
};

struct Settings{
    uint32_t        window_width;
    uint32_t        window_height;
    uint32_t        foreground_color;
    uint32_t        background_color;
    uint32_t        scale_factor;
};


static bool init_settings_from_args(struct Settings *emulator_settings, const int argc, char **argv);

static bool init_emulator(struct Emulator *chip8_emulator, struct Settings emulator_settings);

static void handle_input(struct Machine *chip8);

static void update_screen(struct Emulator chip8_emulator);

static void clear_screen(struct Emulator chip8_emulator, struct Settings emulator_settings);

static void cleanup(struct Emulator chip8_emulator);

#endif //__EMULATOR_H__

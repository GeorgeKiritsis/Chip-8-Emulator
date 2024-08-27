#include "SDL2/SDL.h"
#include <stdbool.h>

#include "../headers/emulator.h"
#include "../headers/chip8.h"

static bool init_settings_from_args(struct Settings *emulator_settings, const int argc, char **argv)
{
    //set default settings // Chip-8 Original Resolution
    *emulator_settings = (struct Settings){ // designated initializer **to make things a bit modern**
        .window_width = 64, 
        .window_height = 32,
        .background_color = 0xFFFFFFFF,
        .foreground_color = 0xFFFF00FF,
        .scale_factor = 10 
    };

    //override default settings from cmd args
    for(int i = 0; i < argc; i++){
        (void)argv[i];
    }

    return true;
}

static bool init_emulator(struct Emulator *chip8_emulator, struct Settings emulator_settings)
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0){
        fprintf(stderr, "[EMULATOR]:Error: Failed to initialize SDL subsystems:%s.\n", SDL_GetError());
        return false;
    }

    chip8_emulator->window = SDL_CreateWindow(
        "Chip-8 Emulator",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        emulator_settings.window_width * emulator_settings.scale_factor,
        emulator_settings.window_height * emulator_settings.scale_factor,
        SDL_WINDOW_ALLOW_HIGHDPI // for highdpi screens (ex Macbook retina display)
    );

    if(!chip8_emulator->window){
        fprintf(stderr, "[EMULATOR]:Error: Failed to create window:%s.\n", SDL_GetError());
        return false;
    }

    chip8_emulator->renderer = SDL_CreateRenderer(
        chip8_emulator->window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    if(!chip8_emulator->renderer){
        fprintf(stderr, "[EMULATOR]:Error: Failed to create renderer:%s.\n", SDL_GetError());
        return false;
    }

    return true;
}

static bool init_chip8(struct Machine *chip8)
{
    chip8->emulator_state = RUNNING;
    return true;
}

static void update_screen(const struct Emulator chip8_emulator)
{
    SDL_RenderPresent(chip8_emulator.renderer);
}

static void clear_screen(const struct Emulator chip8_emulator, const struct Settings emulator_settings)
{
    //working on little Endian // targeting x86_64 asm
    const uint8_t r = (emulator_settings.background_color >> 24) & 0xFF;
    const uint8_t g = (emulator_settings.background_color >> 16) & 0xFF;
    const uint8_t b = (emulator_settings.background_color >>  8) & 0xFF;
    const uint8_t a = (emulator_settings.background_color >>  0) & 0xFF;

    SDL_SetRenderDrawColor(chip8_emulator.renderer, r, g, b, a);
    SDL_RenderClear(chip8_emulator.renderer);
}


static void handle_input(struct Machine *chip8)
{
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                chip8->emulator_state = QUIT;
                return;
        }
    }
}

static void cleanup(struct Emulator chip8_emulator)
{
    SDL_DestroyRenderer(chip8_emulator.renderer);
    SDL_DestroyWindow(chip8_emulator.window);
    SDL_Quit();
}

int main(int argc, char **argv)
{
    //Initialize Emulator Settings
    struct Settings emulator_settings = {0};
    if(!init_settings_from_args(&emulator_settings, argc, argv))
        exit(EXIT_FAILURE);

    //Initialize Emulator
    struct Emulator chip8_emulator = {0};
    if(!init_emulator(&chip8_emulator, emulator_settings))
        exit(EXIT_FAILURE);

    //Initialize Chip-8 machine
    struct Machine chip8 = {0};
    if(!init_chip8(&chip8))
        exit(EXIT_FAILURE);

    //Initial Screen Clear to background_color
    clear_screen(chip8_emulator, emulator_settings);

    //Emulator loop
    while(chip8.emulator_state != QUIT){
        //not clearing screen at every frame
        //Chip-8 has builtin instruction for it

        handle_input(&chip8);

        //TODO:
        //calculate_time()
        //emulate Chip-8 instruction
        //calculate_time() elapsed

        //Chip-8 updates screen at ~60hz
        SDL_Delay(16);

        //update screen @ each frame
        update_screen(chip8_emulator);
    }

    //Final cleanup
    cleanup(chip8_emulator);

    exit(EXIT_SUCCESS);
}

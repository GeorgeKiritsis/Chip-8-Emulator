#include <SDL2/SDL.h>
#include <stdbool.h>

bool init_sdl(void)
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0){
        fprintf(stderr, "[EMULATOR]:Error: Failed to initialize SDL subsystems:%s.\n", SDL_GetError());
        return false;
    }

    return true;
}

void cleanup(void);

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    if(!init_sdl())
        exit(EXIT_FAILURE);

    return 0;
}

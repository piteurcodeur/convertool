#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stb/stb_image.h>
#include <utils.h>


void SDL_ExitWithError(const char *message)
{
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}
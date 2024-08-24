#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stb/stb_image.h>
#include <utils.h>
#include "background.h"
#include <string.h>

DropArea droparea = {0, 0, WINDOW_WIDTH/2, WINDOW_HEIGHT};


void SDL_ExitWithError(const char *message)
{
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

SDL_bool isDropOnArea(PointerPos *_p)
{
    SDL_GetMouseState(&(_p->x), &(_p->y));

    if(_p->x < droparea.maxX && _p->x > droparea.minX && _p->y < droparea.maxY && _p->y > droparea.minY)
    {
        return SDL_TRUE;
    }

    return SDL_FALSE;
    
}


SDL_bool isImageFile(char *filename) {
    if (filename == NULL) {
        return SDL_FALSE;
    }

    char *ext = strrchr(filename, '.');

    if (ext != NULL && 
        (strcmp(ext, ".png") == 0 || strcmp(ext, ".jpg") == 0 ||
         strcmp(ext, ".jpeg") == 0 || strcmp(ext, ".bmp") == 0 ||
         strcmp(ext, ".tga") == 0 || strcmp(ext, ".tiff") == 0 ||
         strcmp(ext, ".tif") == 0 || strcmp(ext, ".ico") == 0)) {
        return SDL_TRUE;
    }

    return SDL_FALSE;
}

#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

typedef struct
{
    int x,y;
} PointerPos;


void SDL_ExitWithError(const char *message);        
SDL_bool isDropOnArea(PointerPos *_p);
SDL_bool isImageFile(char *filename);
void changeTypeName(char *filename, char* type);

void jpg2png(char *input, char *output);

void convertFile(char *input, char *output);

#endif // UTILS_H

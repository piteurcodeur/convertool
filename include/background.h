#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL2/SDL.h>

typedef struct{
    Uint8 r, g, b, a;
} Color;

void changeColor(Color _color, SDL_Renderer *_rend);
void drawline(SDL_Renderer *_rend);        

#endif // UTILS_H
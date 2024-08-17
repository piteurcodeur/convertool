#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL2/SDL.h>

typedef struct{
    Uint8 r, g, b, a;
} Color;

typedef struct{
    int Xstart;
    int Ystart;
    int Xend;
    int Yend;
}lineCoord;

void changeColor(Color _color, SDL_Renderer *_rend);
void drawline(SDL_Renderer *_rend, lineCoord _lc);        

#endif // UTILS_H
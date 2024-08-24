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

typedef struct 
{
    int minX, minY, maxX, maxY;
} DropArea;



void changeColor(Color _color, SDL_Renderer *_rend);
void drawline(SDL_Renderer *_rend, lineCoord _lc);    
void drawRect(SDL_Renderer *_rend, SDL_Rect *_rect, SDL_bool _fill);     

#endif // BACKGROUND_H
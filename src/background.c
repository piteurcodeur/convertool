#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stb/stb_image.h>
#include <utils.h>
#include "background.h"
#include "texte.h"
#include <SDL_ttf.h>

Color WHITE = {255,255,255,255};
Color BLACK = {0,0,0,255};

void changeColor(Color _color, SDL_Renderer *_rend)
{
    if (SDL_SetRenderDrawColor(_rend, _color.r, _color.g, _color.b, SDL_ALPHA_OPAQUE) != 0)
    {
        SDL_ExitWithError("unable to change the color");    
    }
}

void drawline(SDL_Renderer *_rend, lineCoord _lc)
{
    //SDL_RenderSetScale(_rend, 2, 2);

    if (SDL_RenderDrawLine(_rend, _lc.Xstart, _lc.Ystart, _lc.Xend, _lc.Yend) != 0)
    {
        SDL_ExitWithError("unable to draw a line");
    }
}

void drawRect(SDL_Renderer* _rend, SDL_Rect* _rect, SDL_bool _fill)
{
    if (_fill)
    {
        if (SDL_RenderFillRect(_rend, _rect) != 0)
    {
        SDL_ExitWithError("unable to draw rectangle");
    }
    }
    
}


void showText(SDL_Renderer *renderer, Color _color, int X, int Y, int fontSize, char* texte)
{
    //Color c = {56,56,125,100};
    create_texte(renderer, _color, X, Y, fontSize, texte);
}

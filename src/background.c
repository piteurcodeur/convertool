#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stb/stb_image.h>
#include <utils.h>
#include "background.h"


   void changeColor(Color _color, SDL_Renderer *_rend)
   {
        if (SDL_SetRenderDrawColor(_rend, _color.r, _color.g, _color.b, SDL_ALPHA_OPAQUE) != 0)
        {
            SDL_ExitWithError("unable to change the color");    
        }
   }

   void drawline(SDL_Renderer *_rend, lineCoord _lc)
   {

       if (SDL_RenderDrawLine(_rend, _lc.Xstart, _lc.Ystart, _lc.Xend, _lc.Yend) != 0)
       {
           SDL_ExitWithError("unable to draw a line");
       }
}

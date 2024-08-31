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
Color RED = {255,0,0,255};

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
    else
    {
        /* code */
    }
    
    
}


void showText(SDL_Renderer *renderer, Color _color, int X, int Y, int fontSize, char* texte)
{
    //Color c = {56,56,125,100};
    create_texte(renderer, _color, X, Y, fontSize, texte);
}



// Fonction pour initialiser un bouton
Button createButton(SDL_Renderer* renderer, int fontSize, const char* text, int x, int y, int w, int h, SDL_Color textColor) {

    if (TTF_Init() < 0) {
        fprintf(stderr, "Erreur lors de l'initialisation de TTF: %s\n", TTF_GetError());
        SDL_Quit();
    }

    TTF_Font* font = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", fontSize);;
    Button button;
    button.rect = (SDL_Rect){x, y, w, h};
    button.font = font;
    button.text = text;
    button.textColor = textColor;

    // Créer une surface pour le texte
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, textColor);
    if (!surface) {
        fprintf(stderr, "Erreur lors de la création de la surface pour le texte: %s\n", TTF_GetError());
        button.texture = NULL;
        return button;
    }

    // Créer une texture à partir de la surface
    button.texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!button.texture) {
        fprintf(stderr, "Erreur lors de la création de la texture pour le texte: %s\n", SDL_GetError());
    }

    // Libérer la surface
    SDL_FreeSurface(surface);

    return button;
}

// Fonction pour dessiner un bouton
void drawButton(SDL_Renderer* renderer, const Button* button) {
    // Dessiner le rectangle du bouton
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Couleur du rectangle
    SDL_RenderFillRect(renderer, &button->rect);

    // Dessiner le texte du bouton
    if (button->texture) {
        SDL_Rect textRect = {button->rect.x, button->rect.y, button->rect.w, button->rect.h};
        SDL_RenderCopy(renderer, button->texture, NULL, &textRect);
    }
}
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stb/stb_image.h>
#include <utils.h>
#include "background.h"
#include "texte.h"
#include <SDL_ttf.h>

SDL_Color WHITE = {255,255,255,255};
SDL_Color BLACK = {0,0,0,255};
SDL_Color RED = {255,0,0,255};
SDL_Color GREEN = {0,255,0,255};

FontCache fontCache[MAX_FONTS] = {0};
int fontCacheCount = 0;


void changeColor(SDL_Color _color, SDL_Renderer *_rend)
{
    if (SDL_SetRenderDrawColor(_rend, _color.r, _color.g, _color.b, _color.a) != 0)
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

void drawRect(SDL_Renderer* _rend, SDL_Rect* _rect, SDL_bool _fill, SDL_Color _color)
{
    //changeColor(_color, _rend);
    SDL_SetRenderDrawColor(_rend, _color.r, _color.g, _color.b, _color.a);
    SDL_SetRenderDrawBlendMode(_rend, SDL_BLENDMODE_BLEND);
    if (_fill)
    {
        if (SDL_RenderFillRect(_rend, _rect) != 0)
        {
            SDL_ExitWithError("unable to draw rectangle");
        }
    }
    else
    {
        if (SDL_RenderDrawRect(_rend, _rect) != 0)
        {
            SDL_ExitWithError("unable to draw rectangle");
        }
    }
}


// Fonction pour initialiser un bouton
Button createButton(SDL_Renderer* renderer, int fontSize, const char* text, int x, int y, int w, int h, SDL_Color textColor) {

    if (TTF_Init() < 0) {
        fprintf(stderr, "Erreur lors de l'initialisation de TTF: %s\n", TTF_GetError());
        SDL_Quit();
    }

    TTF_Font* font = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", fontSize);
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

void clearText(SDL_Renderer* renderer, SDL_Color backgroundColor, int x, int y, int w, int h) {
    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    SDL_Rect rect = {x, y, w, h};
    if (SDL_RenderFillRect(renderer, &rect) != 0) {
        SDL_ExitWithError("SDL_RenderFillRect Error");
    }
}


// Fonction pour obtenir ou charger une police
TTF_Font* getFont(const char* path, int fontSize) {
    for (int i = 0; i < fontCacheCount; i++) {
        if (strcmp(fontCache[i].path, path) == 0 && fontCache[i].size == fontSize) {
            
            return fontCache[i].font;
        }
    }

    if (fontCacheCount >= MAX_FONTS) {
        printf("Erreur : Cache de polices plein\n");
        return NULL;
    }

    TTF_Font* font = TTF_OpenFont(path, fontSize);
    if (!font) {
        printf("Erreur de chargement de la police : %s\n", TTF_GetError());
        return NULL;
    }

    fontCache[fontCacheCount].path = strdup(path);
    fontCache[fontCacheCount].size = fontSize;
    fontCache[fontCacheCount].font = font;
    fontCacheCount++;
    
    return font;
}

textInfo* createTextTexture(SDL_Renderer *renderer, SDL_Color color, int x, int y, int fontSize, char* text) {
    TTF_Font* font = getFont("C:/Windows/Fonts/arial.ttf", fontSize);
    if (!font) {
        return NULL;
    }

    TextStyle style = {
        .font = font,
        .color = color,
        .size = fontSize,
        .bold = false,
        .italic = false,
        .underline = false
    };

    SDL_Rect rect = {x, y, 0, 0};
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    
    textInfo *_t = (textInfo*)malloc(sizeof(textInfo));
    if (!_t) {
        printf("Erreur: allocation mémoire échouée\n");
        return NULL;
    }

    _t->texture = renderText(renderer, text, style, &rect);
    if(!_t->texture)
    {
        printf("Erreur: création de texture échouée\n");
        free(_t);
        return NULL;
    }
    _t->rect = rect;

    return _t;
    
}


void showText(SDL_Renderer *renderer, textInfo* _text, SDL_bool dynamElt)
{
    if (_text && _text->texture) {
        SDL_RenderCopy(renderer, _text->texture, NULL, &_text->rect);
    } else {
        printf("Erreur : texture ou structure textInfo invalide\n");
    }
    if(dynamElt)
    {
        SDL_DestroyTexture(_text->texture);
    }
}

// Fonction pour libérer la mémoire du cache de polices
void cleanupFontCache() {
    for (int i = 0; i < fontCacheCount; i++) {
        printf("Police %d - Chemin : %s, Adresse : %p, size : %d\n", 
            i, 
            fontCache[i].path ? fontCache[i].path : "NULL", 
            (void*)fontCache[i].font, fontCache[i].size);
    }
}
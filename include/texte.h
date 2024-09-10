#ifndef TEXTE_H_
#define TEXTE_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL_ttf.h>

// Structure définissant un style de texte
typedef struct {
    TTF_Font* font;
    SDL_Color color;
    int size;
    bool bold;
    bool italic;
    bool underline;
} TextStyle;

// Structure définissant un bouton avec texte
typedef struct {
    SDL_Rect rect;
    SDL_Color bgColor;
    SDL_Color textColor;
    SDL_Color hoverColor;
    char* text;
    TTF_Font* font;
    bool isHovered;
    bool isPressed;
} Button2;

// Fonctions pour la gestion du texte et des boutons
void create_texte(SDL_Renderer *renderer, SDL_Color _color, int X, int Y, int fontSize, char* texte);
SDL_Texture* renderText(SDL_Renderer* renderer, const char* text, TextStyle style, SDL_Rect* textRect);
void drawTextWithShadow(SDL_Renderer* renderer, const char* text, TextStyle style, int x, int y, SDL_Color shadowColor, int shadowOffset);
void drawTextGradient(SDL_Renderer* renderer, const char* text, TextStyle style, int x, int y, SDL_Color startColor, SDL_Color endColor);
void drawTextOutline(SDL_Renderer* renderer, const char* text, TextStyle style, int x, int y, SDL_Color outlineColor, int outlineThickness);
Button2 createButton2(int x, int y, int w, int h, char* text, TTF_Font* font, SDL_Color bgColor, SDL_Color textColor, SDL_Color hoverColor);
void destroyButton(Button2* btn);
void drawButton2(SDL_Renderer* renderer, Button2* btn);
bool isPointInRect(int x, int y, SDL_Rect* rect);

#endif // TEXTE_H_

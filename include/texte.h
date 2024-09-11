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

/**
 * @brief Create a texte object
 * 
 * @param renderer 
 * @param _color 
 * @param X 
 * @param Y 
 * @param fontSize 
 * @param texte 
 */
void create_texte(SDL_Renderer *renderer, SDL_Color _color, int X, int Y, int fontSize, char* texte);

/**
 * @brief create an object texte and render it
 * 
 * @param renderer 
 * @param text 
 * @param style 
 * @param textRect 
 * @return SDL_Texture* 
 */
SDL_Texture* renderText(SDL_Renderer* renderer, const char* text, TextStyle style, SDL_Rect* textRect);

/**
 * @brief render a text with shadow
 * 
 * @param renderer 
 * @param text 
 * @param style 
 * @param x 
 * @param y 
 * @param shadowColor 
 * @param shadowOffset 
 */
void drawTextWithShadow(SDL_Renderer* renderer, const char* text, TextStyle style, int x, int y, SDL_Color shadowColor, int shadowOffset);

/**
 * @brief render a text with color gradient
 * 
 * @param renderer 
 * @param text 
 * @param style 
 * @param x 
 * @param y 
 * @param startColor 
 * @param endColor 
 */
void drawTextGradient(SDL_Renderer* renderer, const char* text, TextStyle style, int x, int y, SDL_Color startColor, SDL_Color endColor);

/**
 * @brief render a text with outline
 * 
 * @param renderer 
 * @param text 
 * @param style 
 * @param x 
 * @param y 
 * @param outlineColor 
 * @param outlineThickness 
 */
void drawTextOutline(SDL_Renderer* renderer, const char* text, TextStyle style, int x, int y, SDL_Color outlineColor, int outlineThickness);

/**
 * @brief Create a Button2 object
 * 
 * @param x 
 * @param y 
 * @param w 
 * @param h 
 * @param text 
 * @param font 
 * @param bgColor 
 * @param textColor 
 * @param hoverColor 
 * @return Button2 
 */
Button2 createButton2(int x, int y, int w, int h, char* text, TTF_Font* font, SDL_Color bgColor, SDL_Color textColor, SDL_Color hoverColor);

/**
 * @brief destroy a Button object
 * 
 * @param btn 
 */
void destroyButton(Button2* btn);

/**
 * @brief draw a Button object, used for updating the button
 * 
 * @param renderer 
 * @param btn 
 */
void drawButton2(SDL_Renderer* renderer, Button2* btn);

/**
 * @brief control if the mouse pointer is in the rectangle in parameter
 *          used for detecting a button hovered
 * @param x 
 * @param y 
 * @param rect 
 * @return true 
 * @return false 
 */
bool isPointInRect(int x, int y, SDL_Rect* rect);

#endif // TEXTE_H_

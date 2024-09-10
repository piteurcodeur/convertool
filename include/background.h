#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL2/SDL.h>
#include <SDL_ttf.h>


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

typedef struct {
    SDL_Rect rect;
    SDL_Texture* texture;
    SDL_Color textColor;
    TTF_Font* font;
    const char* text;
} Button;

extern SDL_Color BLACK;
extern SDL_Color WHITE;
extern SDL_Color RED;

/**
 * @brief changer la couleur SDL active sur le rendu
 * 
 * @param _color structure couleur RGBa
 * @param _rend le rendu SDL
 */
void changeColor(SDL_Color _color, SDL_Renderer *_rend);

/**
 * @brief dessiner une ligne sur un renderer
 * 
 * @param _rend le rendu SDL
 * @param _lc structure des coordonnées de la ligne
 */
void drawline(SDL_Renderer *_rend, lineCoord _lc);    

/**
 * @brief dessiner un rectangle sur un renderer
 * 
 * @param _rend le rendu SDL
 * @param _rect structure de rectangle contenant les coordonnées
 * @param _fill le rectangle sera rempli de la couleur SDL actuelle si fill = true
 */
void drawRect(SDL_Renderer *_rend, SDL_Rect *_rect, SDL_bool _fill);     

/**
 * @brief afficher un texte custom sur un renderer
 * 
 * @param renderer le rendu SDL
 * @param _color structure couleur RGBa du texte
 * @param X ordonnée
 * @param Y abscisse
 * @param fontSize taille du texte
 * @param texte texte à afficher
 */
void showText(SDL_Renderer *renderer, SDL_Color _color, int X, int Y, int fontSize, char* texte);

/**
 * @brief Créer un objet Button
 * 
 * @param renderer le rendu SDL
 * @param fontSize taille du texte
 * @param text texte du bouton
 * @param x abscisse
 * @param y ordonnée
 * @param w longueur
 * @param h largeur
 * @param textColor couleur SDL du texte
 *  
 * @return object Button initialisé
 */
Button createButton(SDL_Renderer* renderer, int fontSize, const char* text, int x, int y, int w, int h, SDL_Color textColor);

/**
 * @brief afficher le bouton sur le rendu SDL
 * 
 * @param renderer rendu SDL
 * @param button bouton à afficher
 */
void drawButton(SDL_Renderer *renderer, const Button *button);

#endif // BACKGROUND_H
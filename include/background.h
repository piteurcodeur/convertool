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
extern SDL_Color GREEN;

// Structure globale pour stocker les polices chargées
typedef struct {
    char* path;
    int size;
    TTF_Font* font;
} FontCache;

#define MAX_FONTS 10

typedef struct
{
    SDL_Texture* texture;
    SDL_Rect rect;

} textInfo;


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
void drawRect(SDL_Renderer *_rend, SDL_Rect *_rect, SDL_bool _fill, SDL_Color _color);     

/**
 * @brief Afficher le texte grace à la texture créée
 * 
 * @param renderer Renderer sur lequel afficher le texte
 * @param _text Contient la texture et le rectangle de coordonnées
 */
void showText(SDL_Renderer *renderer, textInfo* _text, SDL_bool dynamElt);

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

void clearText(SDL_Renderer* renderer, SDL_Color backgroundColor, int x, int y, int w, int h);
TTF_Font* getFont(const char* path, int fontSize);

/**
 * @brief Create a Text Texture object
 * 
 * @param renderer 
 * @param color 
 * @param x 
 * @param y 
 * @param fontSize 
 * @param text 
 * @return textInfo* 
 */
textInfo* createTextTexture(SDL_Renderer *renderer, SDL_Color color, int x, int y, int fontSize, char *text);

void cleanupFontCache();

#endif // BACKGROUND_H
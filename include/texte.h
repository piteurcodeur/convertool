#ifndef texte_h_
#define texte_h_

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <background.h>

#endif




void create_texte(SDL_Renderer *renderer, Color _color, int X, int Y, int fontSize, char* texte) {
    
    // Initialisation de SDL_ttf
    if (TTF_Init() < 0) {
        printf("Impossible d'initialiser SDL_ttf : %s\n", TTF_GetError());
        exit(1);
    }

    // Charge une police depuis un fichier, avec une taille de point à 50
    TTF_Font* Font = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", fontSize);
    if (!Font) {
        printf("Erreur de création de la police : %s\n", TTF_GetError());
        TTF_Quit();
        exit(1);
    }

    // Couleur du texte (ici rouge)
    SDL_Color TextColor = {_color.r, _color.g, _color.b, _color.a};

    // On rend un texte sur une surface SDL, en utilisant notre police et notre couleur
    SDL_Surface* TextSurface = TTF_RenderText_Solid(Font, texte, TextColor);
    if (!TextSurface) {
        printf("Erreur de rendu du texte : %s\n", TTF_GetError());
        TTF_CloseFont(Font);
        TTF_Quit();
        exit(1);
    }

    // Convertir la surface de texte en texture
    SDL_Texture* TextTexture = SDL_CreateTextureFromSurface(renderer, TextSurface);
    if (!TextTexture) {
        printf("Erreur lors de la création de la texture : %s\n", SDL_GetError());
        SDL_FreeSurface(TextSurface);
        TTF_CloseFont(Font);
        TTF_Quit();
        exit(1);
    }
   

    // Afficher le texte
    SDL_Rect DstRect = {X, Y, TextSurface->w, TextSurface->h};
    SDL_RenderCopy(renderer, TextTexture, NULL, &DstRect);

    // Libère notre surface et notre police
    SDL_FreeSurface(TextSurface);
    TTF_CloseFont(Font);

    // Libère la texture
    SDL_DestroyTexture(TextTexture);

    // Fermeture de SDL_ttf
    TTF_Quit();
}
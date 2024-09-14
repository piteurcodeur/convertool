
typedef struct
{
    SDL_Texture* texture;
    SDL_Rect* rect;

} textInfo;

SDL_Texture* renderText(SDL_Renderer* renderer, const char* text, TextStyle style, SDL_Rect* textRect) {
    TTF_SetFontStyle(style.font, (style.bold ? TTF_STYLE_BOLD : 0) | 
                                 (style.italic ? TTF_STYLE_ITALIC : 0) | 
                                 (style.underline ? TTF_STYLE_UNDERLINE : 0));

    SDL_Surface* surface = TTF_RenderUTF8_Blended(style.font, text, style.color);
    if (!surface) {
        printf("Erreur lors du rendu du texte: %s\n", TTF_GetError());
        return NULL;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        printf("Erreur lors de la création de la texture: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return NULL;
    }

    textRect->w = surface->w;
    textRect->h = surface->h;

    SDL_FreeSurface(surface);
    return texture;
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
        TTF_CloseFont(font);
        return NULL;
    }

    _t->texture = renderText(renderer, text, style, &rect);
    _t->rect = &rect;

    return _t;
    
}

void showText(SDL_Renderer *renderer, textInfo* _text)
{
    changeColor(BLACK, renderer);
    printf("showtext\n");
    
    SDL_RenderCopy(renderer, _text->texture, NULL, _text->rect);
    SDL_DestroyTexture(_text->texture);
    
}
#include "texte.h"

void create_texte(SDL_Renderer *renderer, SDL_Color _color, int X, int Y, int fontSize, char* texte) {
    if (TTF_Init() < 0) {
        printf("Impossible d'initialiser SDL_ttf : %s\n", TTF_GetError());
        exit(1);
    }

    TTF_Font* Font = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", fontSize);
    if (!Font) {
        printf("Erreur de création de la police : %s\n", TTF_GetError());
        TTF_Quit();
        exit(1);
    }

    SDL_Surface* TextSurface = TTF_RenderText_Solid(Font, texte, _color);
    if (!TextSurface) {
        printf("Erreur de rendu du texte : %s\n", TTF_GetError());
        TTF_CloseFont(Font);
        TTF_Quit();
        exit(1);
    }

    SDL_Texture* TextTexture = SDL_CreateTextureFromSurface(renderer, TextSurface);
    if (!TextTexture) {
        printf("Erreur lors de la création de la texture : %s\n", SDL_GetError());
        SDL_FreeSurface(TextSurface);
        TTF_CloseFont(Font);
        TTF_Quit();
        exit(1);
    }

    SDL_Rect DstRect = {X, Y, TextSurface->w, TextSurface->h};
    SDL_RenderCopy(renderer, TextTexture, NULL, &DstRect);

    SDL_FreeSurface(TextSurface);
    TTF_CloseFont(Font);
    SDL_DestroyTexture(TextTexture);
    TTF_Quit();
}

SDL_Texture* renderText(SDL_Renderer* renderer, const char* text, TextStyle style, SDL_Rect* textRect) {
    TTF_SetFontStyle(style.font, (style.bold ? TTF_STYLE_BOLD : 0) | 
                                 (style.italic ? TTF_STYLE_ITALIC : 0) | 
                                 (style.underline ? TTF_STYLE_UNDERLINE : 0));

    SDL_Surface* surface = TTF_RenderText_Blended(style.font, text, style.color);
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

void drawTextWithShadow(SDL_Renderer* renderer, const char* text, TextStyle style, int x, int y, SDL_Color shadowColor, int shadowOffset) {
    SDL_Rect shadowRect = {x + shadowOffset, y + shadowOffset, 0, 0};
    SDL_Rect textRect = {x, y, 0, 0};

    TextStyle shadowStyle = style;
    shadowStyle.color = shadowColor;

    SDL_Texture* shadowTexture = renderText(renderer, text, shadowStyle, &shadowRect);
    SDL_Texture* textTexture = renderText(renderer, text, style, &textRect);

    if (shadowTexture && textTexture) {
        SDL_RenderCopy(renderer, shadowTexture, NULL, &shadowRect);
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
        SDL_DestroyTexture(shadowTexture);
        SDL_DestroyTexture(textTexture);
    }
}

void drawTextGradient(SDL_Renderer* renderer, const char* text, TextStyle style, int x, int y, SDL_Color startColor, SDL_Color endColor) {
    int textLength = strlen(text);
    for (int i = 0; i < textLength; i++) {
        char currentChar[2] = {text[i], '\0'};
        SDL_Rect charRect = {x, y, 0, 0};

        float t = (float)i / (float)(textLength - 1);
        SDL_Color currentColor = {
            startColor.r + (endColor.r - startColor.r) * t,
            startColor.g + (endColor.g - startColor.g) * t,
            startColor.b + (endColor.b - startColor.b) * t,
            startColor.a + (endColor.a - startColor.a) * t
        };

        TextStyle charStyle = style;
        charStyle.color = currentColor;

        SDL_Texture* charTexture = renderText(renderer, currentChar, charStyle, &charRect);
        if (charTexture) {
            SDL_RenderCopy(renderer, charTexture, NULL, &charRect);
            SDL_DestroyTexture(charTexture);
        }

        x += charRect.w;
    }
}

void drawTextOutline(SDL_Renderer* renderer, const char* text, TextStyle style, int x, int y, SDL_Color outlineColor, int outlineThickness) {
    SDL_Rect textRect = {x, y, 0, 0};
    TextStyle outlineStyle = style;
    outlineStyle.color = outlineColor;

    for (int dx = -outlineThickness; dx <= outlineThickness; dx++) {
        for (int dy = -outlineThickness; dy <= outlineThickness; dy++) {
            if (dx != 0 || dy != 0) {
                SDL_Rect outlineRect = {x + dx, y + dy, 0, 0};
                SDL_Texture* outlineTexture = renderText(renderer, text, outlineStyle, &outlineRect);
                if (outlineTexture) {
                    SDL_RenderCopy(renderer, outlineTexture, NULL, &outlineRect);
                    SDL_DestroyTexture(outlineTexture);
                }
            }
        }
    }

    SDL_Texture* textTexture = renderText(renderer, text, style, &textRect);
    if (textTexture) {
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
        SDL_DestroyTexture(textTexture);
    }
}

Button2 createButton2(int x, int y, int w, int h, char* text, TTF_Font* font, SDL_Color bgColor, SDL_Color textColor, SDL_Color hoverColor) {
    Button2 btn = {
        {x, y, w, h},
        bgColor,
        textColor,
        hoverColor,
        text,
        font,
        false,
        false
    };
    btn.text = SDL_strdup(text);
    return btn;
}

void destroyButton(Button2* btn) {
    SDL_free(btn->text);
}

void drawButton2(SDL_Renderer* renderer, Button2* btn) {
    SDL_Color currentBgColor = btn->bgColor;
    if (btn->isPressed) {
        currentBgColor.r = (Uint8)(currentBgColor.r * 0.8);
        currentBgColor.g = (Uint8)(currentBgColor.g * 0.8);
        currentBgColor.b = (Uint8)(currentBgColor.b * 0.8);
    } else if (btn->isHovered) {
        currentBgColor.r = (Uint8)(btn->hoverColor.r);
        currentBgColor.g = (Uint8)(btn->hoverColor.g);
        currentBgColor.b = (Uint8)(btn->hoverColor.b);

        btn->textColor = (SDL_Color){0,0,0,255};
    }

    SDL_SetRenderDrawColor(renderer, currentBgColor.r, currentBgColor.g, currentBgColor.b, currentBgColor.a);
    SDL_RenderFillRect(renderer, &btn->rect);

    SDL_Rect textRect;
    SDL_Texture* textTexture = renderText(renderer, btn->text, (TextStyle){btn->font, btn->textColor, 0, false, false, false}, &textRect);
    if (textTexture) {
        textRect.x = btn->rect.x + (btn->rect.w - textRect.w) / 2;
        textRect.y = btn->rect.y + (btn->rect.h - textRect.h) / 2;
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
        SDL_DestroyTexture(textTexture);
    }
}

bool isPointInRect(int x, int y, SDL_Rect* rect) {
    return (x >= rect->x && x < rect->x + rect->w &&
            y >= rect->y && y < rect->y + rect->h);
}

#ifndef TTF_H
#define TTF_H

#include "common.h"
#include "renderer.h"


typedef struct 
{
    TTF_Font* font;
    SDL_Color color;
} Font;


Font* NewFont();
void DestroyFont(Font* font);
void RenderText(SDL_Renderer* renderer, Font* f, char* text, SDL_Rect* point);
void RenderHp(SDL_Renderer* renderer, Font* f, int hp, SDL_Rect* point);

#endif // TTF_H
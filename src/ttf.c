#include "ttf.h"

Font* NewFont(){
    Font* font = (Font*)calloc(1,sizeof(Font));
    // font->font = TTF_OpenFont("./assets/font/AldotheApache.ttf", 20);
    font->font = TTF_OpenFont("./assets/font/Gameplay.ttf", 25);
    SDL_Color color = { 255, 255, 0 };
    font->color = color;
    return font;
}

void DestroyFont(Font* font){
    TTF_CloseFont(font->font);
    free(font);
}

void RenderText(SDL_Renderer* renderer, Font* f, char* text, SDL_Rect* point){
    SDL_Surface* surface = TTF_RenderText_Solid(f->font, text, f->color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, point);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void RenderInt(SDL_Renderer* renderer, Font* f, int num, SDL_Rect* point){
    char* app = "";
    sprintf(app, "%d", num);
    SDL_Surface* surface = TTF_RenderText_Solid(f->font, app, f->color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, point);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}
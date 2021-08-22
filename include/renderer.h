#ifndef RENDERER_H
#define RENDERER_H

#include "common.h"

typedef struct 
{
    List* Animations;
} Animator;

typedef struct 
{
    char* Name;
    int TotFrames;
    int currFrame;
    char* texture_path;
    double TimeFrame;
    double DelayFrame;
    Size* FrameSize;
    List* list;
} Animation;

// texture
int RenderingTexture(SDL_Renderer* renderer, SDL_Texture* tex, Point* p, Size* s);
int RenderingPath(SDL_Renderer* renderer, char* path, Point* p, Size* s);
SDL_Texture* NewTexture(SDL_Renderer* renderer, char* path_file);
SDL_Rect* NewRect(Point* p, Size* s);
void DestroyRect(SDL_Rect* rect);

// animation
Animator* NewAnimator();
void DestroyAnimator(Animator* animator);
Animation* NewAnimation(char* name_animation, char* texture_path, SDL_Rect* src, int nFrames, double TimeFrame);
void DestroyListAnimation(List* animations);
void DestroyAnimation(Animation* anim);

boolean RenderingThisAnimation(SDL_Renderer* r, Animator* anim, char* animation_name, Point* p, double deltatime);
boolean RenderingListAnimation(SDL_Renderer* r, Animation* anim, SDL_Rect* dst, double deltatime);
void RenderingAnimation(SDL_Renderer* r, char* t_p, SDL_Rect* src, SDL_Rect* dst);

// window
void CloseWindow(SDL_Renderer* r, SDL_Window* win);

#endif // RENDERER_H
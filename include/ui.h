#ifndef UI_H
#define UI_H

#include "common.h"
#include "renderer.h"

typedef struct 
{
    List* UiList;
} Interface;

typedef struct 
{
    char* txt_path;
    Point* position;
    Size*  size;
} UI;

// INTERFACE
Interface* NewInterface();
void AddUiList(Interface* i, Point* p, Size* s, char* texture_path);
void UpdateInterface(SDL_Renderer* renderer, Interface* i, double dt);
void DestroyInterface(Interface* i);

// UI
UI* NewUI(Point* p, Size* s, char* texture_path);
void RenderingUI(SDL_Renderer* renderer, UI* ui);
void DestroyUI(UI* ui);

#endif // UI_H
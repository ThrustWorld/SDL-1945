#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <common.h>
#include <renderer.h>

typedef struct
{
    char* texture_path;
    Point* position;
    Size* texture_size;
    boolean IsActive;
    SDL_Rect* MyRect;
} GameObject;

enum IslandsType{Normal = 0, Vulcan, Sand};
typedef enum IslandsType_ IslandsType;

GameObject* NewGameObject(Point* pos, Size* texture_size, char* texture_path);

void RenderGameObject(SDL_Renderer* render, GameObject* go);
void GenericAddElemList(List* l, int n, char* elem, int type);

GameObject* NewIsland(IslandsType it);
void RenderGameObjectList(SDL_Renderer* renderer, List* goList, boolean bg, float deltaTime);
void RenderActiveGameObject(SDL_Renderer* renderer, GameObject* go, boolean bg);

void DestroyGameObject(GameObject* go);

#endif // GAMEOBJECT_H
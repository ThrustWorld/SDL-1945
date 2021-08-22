#ifndef CHARACTER_H
#define CHARACTER_H

#include "gameobject.h"
#include "bullet.h"

typedef struct
{
    double Hp;
    float Speed;
    List* bullets;
    GameObject* Go;
    Animator* Animator_;
} Character;

Character* NewCharacter(int hp, float speed, char* path, Point* p, Size* s);
void UpdateCharacter(SDL_Renderer* render, Character* c, double dt);

void AddAnimation(Character* c, char* animation_name, char* texture_name, SDL_Rect* rect, int frames, double timeFrame);

void DestroyCharacter(Character* c);

#endif // CHARACTER_H
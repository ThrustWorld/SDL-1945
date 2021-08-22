#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"
#include "inputsystem.h"
#include "ui.h"
#include "ttf.h"

typedef struct
{
    Character* Character_;
    int Lives;
    int score;
    boolean IsAlive;
    boolean IsDead;
    GameObject* life1;
    GameObject* life2;
    GameObject* life3;
    InputSystem* Input;
    Font* font;
    Mix_Chunk* explosion;
} Player;


Player* NewPlayer(Point* p, Size* s, InputSystem* input, int hp, float speed, char* text_path);

boolean UpdatePlayer(SDL_Renderer* renderer, SDL_Event* events, Player* player, double dt);
void DestroyPlayer(Player* p);

#endif /*PLAYER_H*/
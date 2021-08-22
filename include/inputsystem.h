#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include <common.h>
#include <list.h>
#include <character.h>
#include <bullet.h>

typedef struct
{
    boolean IsActive;
    SDL_Scancode up;
    SDL_Scancode down;
    SDL_Scancode left;
    SDL_Scancode right;
    SDL_Scancode shoot;
    Mix_Chunk* explosion;
} InputSystem;

InputSystem* NewInputSystem(char* system_buttons);
void DestroyInputSystem(InputSystem* input_);
void init_buttons(InputSystem* inputsys, char* system_movement);

void Movement(SDL_Event* event, InputSystem* inputSys, Character* c, double delta_time);
boolean UpdateInputSystem(SDL_Event* event, InputSystem* inputSys, Character* c, double delta_time);

void shoot (Character* c);

#endif // INPUT_H
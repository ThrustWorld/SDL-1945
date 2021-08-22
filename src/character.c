#include <character.h>

Character* NewCharacter(int hp, float speed, char* path, Point* p, Size* s){
    Character* c = (Character*)calloc(1, sizeof(Character));
    c->Hp = hp;
    c->Speed = speed;
    c->bullets = NewList();
    c->Go = NewGameObject(p, s, path);
    c->Animator_ = NewAnimator();
    return c;
}

void AddAnimation(Character* c, char* animation_name, char* texture_name, SDL_Rect* rect, int frames, double timeFrame){
    // Animation* anim = NewAnimation(animation_name, texture_name, rect, frames);
    AddElemList(c->Animator_->Animations, NewAnimation(animation_name, texture_name, rect, frames, timeFrame));
}

void UpdateCharacter(SDL_Renderer* render, Character* c, double dt){
    if (c->Go->IsActive)
    {
        RenderingThisAnimation(render, c->Animator_, (char*)"main", c->Go->position, dt);
        //RenderGameObject(render, c->Go);
    }
    else{
        //printf("character morto\n");
    }
}

void DestroyCharacter(Character* c){
    DestroyGameObject(c->Go);
    DestroyList(c->bullets);
    DestroyAnimator(c->Animator_);
    free(c);
}
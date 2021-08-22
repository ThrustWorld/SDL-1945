#include "player.h"

Player* NewPlayer(Point* p, Size* s, InputSystem* input, int hp, float speed, char* text_path){
    Player* player = (Player*)calloc(1, sizeof(Player));
    player->Character_ = NewCharacter(hp, speed, text_path, p,s);
    player->Lives = 3;
    player->IsAlive = true;
    player->IsDead = false;
    player->score = 0;
    player->explosion = Mix_LoadWAV("./assets/audio/snd_explosion2.wav");
    Mix_VolumeChunk(player->explosion, SDL_MIX_MAXVOLUME / 12);
    player->life1 = NewGameObject(NewPoint(100,HEIGHT_WINDOW-90), NewSize(40, 40), "assets/ui/life.png");
    player->life2 = NewGameObject(NewPoint(55,HEIGHT_WINDOW-90), NewSize(40, 40), "assets/ui/life.png");
    player->life3 = NewGameObject(NewPoint(10,HEIGHT_WINDOW-90), NewSize(40, 40), "assets/ui/life.png");
    GenericAddElemList(player->Character_->bullets, 10, "bullet", playerBullet);
    AddAnimation(player->Character_, "main", "assets/player/myplane_strip3.png", NewRect(NewPoint(player->Character_->Go->position->x,0), player->Character_->Go->texture_size), 3, 0.03f);
    AddAnimation(player->Character_, "explosion", "assets/player/explosion2_strip7.png", NewRect(NewPoint(player->Character_->Go->position->x,0), player->Character_->Go->texture_size), 7, 0.1f);
    player->Input = input;
    player->font = NewFont();
    return player;
}

boolean UpdatePlayer(SDL_Renderer* renderer, SDL_Event* events, Player* player, double dt){
    UpdateBullets(renderer, player->Character_->bullets, dt);

    switch(player->Lives){
        case 3:
            RenderGameObject(renderer, player->life1);
            RenderGameObject(renderer, player->life2);
            RenderGameObject(renderer, player->life3);
            break;
        case 2:
            RenderGameObject(renderer, player->life1);
            RenderGameObject(renderer, player->life2);
            break;
        case 1:
            RenderGameObject(renderer, player->life1);
            break;
    }

    if(player->Character_->Hp > 0){
        //player->Character_->Hp -= 0.05f;
    }
    else if (player->Character_->Hp <= 0 && player->Lives > 0 && player->IsAlive)
    {
        player->Lives--;
        player->Character_->Go->IsActive = false;
        player->IsAlive = false;
        player->Input->IsActive = false;
    }

    if (player->IsAlive == false && player->Lives != 0)
    {
        Mix_PlayChannel(-1, player->explosion, 0);
        if(RenderingThisAnimation(renderer, player->Character_->Animator_, "explosion", player->Character_->Go->position, dt)){
            player->Character_->Hp = 100;
            player->Character_->Go->IsActive = true;
            player->IsAlive = true;
            player->Input->IsActive = true;
            player->Character_->Go->position = NewPoint(290,180);
        }
    }
    else if (player->IsAlive == false && player->Lives == 0 && !player->IsDead){
        Mix_PlayChannel(-1, player->explosion, 0);
        if(RenderingThisAnimation(renderer, player->Character_->Animator_, "explosion", player->Character_->Go->position, dt)){
            player->Character_->Go->IsActive = false;
            player->IsDead = true;
            player->Input->IsActive = false;
        }
    }
    
    RenderInt(renderer, player->font, player->score, NewRect(NewPoint(200, HEIGHT_WINDOW-42), NewSize(20,20)));

    UpdateCharacter(renderer, player->Character_, dt);
    
    RenderingPath(renderer, (char*)"./assets/ui/hp.png", NewPoint(12, HEIGHT_WINDOW -40), NewSize(126 * player->Character_->Hp / 100, 13));

    int done = UpdateInputSystem(events, player->Input, player->Character_, dt);

    if (!done && !player->IsAlive && player->IsDead)
    {
        SDL_Delay(1000);
        done = true;
    }
    return done;
}

void DestroyPlayer(Player* p){
    DestroyCharacter(p->Character_);
    DestroyGameObject(p->life1);
    DestroyGameObject(p->life2);
    DestroyGameObject(p->life3);
    DestroyInputSystem(p->Input);
    DestroyFont(p->font);
    Mix_FreeChunk(p->explosion);
    free(p);
}
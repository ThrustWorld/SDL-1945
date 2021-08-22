#ifndef BULLET_H
#define BULLET_H

#include "common.h"
#include "gameobject.h"
#include "renderer.h"


typedef struct
{
    GameObject* Go;
    int Damage;
    float Speed;
} Bullet;

enum BulletType_ {normal = 0, playerBullet, enemyBullet};
typedef enum BulletType_ BulletType; 

Bullet* NewBullet(BulletType bulletType);
void RenderingBullet(SDL_Renderer* renderer, Bullet* b);
void UpdateBullets(SDL_Renderer* renderer, List* bullets, double delta_time);

void DestroyBullet(Bullet* b);


#endif /*BULLET_H*/
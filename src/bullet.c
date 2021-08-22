#include "bullet.h"

Bullet* NewBullet(BulletType bulletType){
    Bullet* bullet_ = (Bullet*)calloc(1, sizeof(Bullet));
    if (bulletType == playerBullet)
    {
        bullet_->Damage = 30;
        bullet_->Speed = 100;
        bullet_->Go = NewGameObject(NewPoint(20,20), NewSize(15,15), (char*)"./assets/player/bullet.png");
        bullet_->Go->IsActive = false;
    }
    else if (bulletType == enemyBullet)
    {
        bullet_->Damage = 20;
        bullet_->Speed = -50;
        bullet_->Go = NewGameObject(NewPoint(20,20), NewSize(10,10), (char*)"./assets/enemy/enemyBullet.png");
        bullet_->Go->IsActive = false;
    }
    else if (bulletType == normal)
    {
        bullet_->Damage = 10;
        bullet_->Speed = 10;
        bullet_->Go = NewGameObject(NewPoint(20,20), NewSize(10,10), (char*)"./assets/enemy/enemybullet2.png");
        bullet_->Go->IsActive = false;
    }
    return bullet_;
}

void DestroyBullet(Bullet* b){
    DestroyGameObject(b->Go);
    free(b);
}

void UpdateBullets(SDL_Renderer* renderer, List* bullets, double delta_time){
    int count = 0;
    Node* each = bullets->__head;
    Bullet* bullet_free;
    while (each)
    {
        Node* next = each->next;
        //printf("bullet[%d] is active -> %d\n", count, ((Bullet*)each->data)->Go->IsActive);
        if (((Bullet*)each->data)->Go->IsActive == true){
            bullet_free = (Bullet*)each->data;
            bullet_free->Go->position->y += -1 * bullet_free->Speed * delta_time;
            RenderingBullet(renderer, bullet_free);
        }
        count++;
        each = next;
    }
    each = NULL;
    bullet_free = NULL;
}

void RenderingBullet(SDL_Renderer* renderer, Bullet* b){
    if (b->Speed > 0 && b->Go->position->y < 0)
    {
        b->Go->IsActive = false; // only with list in config
    }
    if (b->Speed < 0 && b->Go->position->y > (HEIGHT_WINDOW - 100))
    {
        b->Go->IsActive = false;
    }
    else{
        // printf("rendering bullet\n");
        RenderGameObject(renderer, b->Go);        
    }
}
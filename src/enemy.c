#include "enemy.h"

Enemy* NewEnemy(Size* s, char* texture, int score){
    Enemy* enemy = (Enemy*)calloc(1, sizeof(Enemy));
    enemy->Character_ = NewCharacter(50, 30, texture, NewPoint(0,0), s);
    enemy->score = score;
    enemy->TimeShoot = 1;
    enemy->IsAlive = true;
    enemy->IsDead = false;
    enemy->shoot = Mix_LoadWAV("./assets/audio/snd_explosion1.wav");
    Mix_VolumeChunk(enemy->shoot, SDL_MIX_MAXVOLUME / 14);
    enemy->explosion = Mix_LoadWAV("./assets/audio/snd_explosion2.wav");
    Mix_VolumeChunk(enemy->explosion, SDL_MIX_MAXVOLUME / 15);
    GenericAddElemList(enemy->Character_->bullets, 10, (char*)"bullet", enemyBullet);
    AddAnimation(enemy->Character_, (char*)"main", texture, NewRect(enemy->Character_->Go->position, NewSize(32,32)), 3, 0.05f);
    AddAnimation(enemy->Character_, (char*)"explosion", (char*)"./assets/enemy/explosion1_strip6.png", NewRect(enemy->Character_->Go->position, NewSize(32,32)), 6, 0.1f);
    enemy->Character_->Go->position->x = GetRandomInRange(100, WIDTH_WINDOW - (100 + s->Width));
    enemy->Character_->Go->position->y = -GetRandomInRange(s->Height, s->Height - 300);
    return enemy;    
}

void UpdateEnemy(SDL_Renderer* renderer, Enemy* enemy, double dt){
    UpdateBullets(renderer, enemy->Character_->bullets, dt);
    ShootEnemy(enemy, dt);

    if (enemy->Character_->Hp <= 0 && !enemy->IsDead)
    {
        enemy->IsAlive = false;
        enemy->Character_->Go->IsActive = false;
        Mix_PlayChannel(-1, enemy->explosion, 0);
        if(RenderingThisAnimation(renderer, enemy->Character_->Animator_, "explosion", enemy->Character_->Go->position, dt)){
            enemy->IsDead = true;
        }
    }

    RespawnEnemy(enemy);

    UpdateCharacter(renderer, enemy->Character_, dt);
}

void ShootEnemy(Enemy* enemy, double dt){
    enemy->TimeShoot -= dt;
    if (enemy->TimeShoot <= 0)
    {
        ShootEnemyBullets(enemy);
        enemy->TimeShoot = GetRandomInRange(2,7);
    }
}

void ShootEnemyBullets(Enemy* e){
    if (e->Character_->Go->position->y > 0)
    {
        int count = 0;
        int index = 0;
        Node* each = e->Character_->bullets->__head;
        Bullet* bullet_app;
        while (each)
        {
            Node* next = each->next;
            if (((Bullet*)each->data)->Go->IsActive == false)
            {
                bullet_app = ((Bullet*)each->data); 
                bullet_app->Go->IsActive = true;
                Mix_PlayChannel(-1, e->shoot, 0);
                bullet_app->Go->position->x = e->Character_->Go->position->x + (e->Character_->Go->texture_size->Width * 0.5f) - (bullet_app->Go->texture_size->Width * 0.5f);
                bullet_app->Go->position->y = e->Character_->Go->position->y + bullet_app->Go->texture_size->Height;
                index = count;
                //printf("count: %d\nactive: %d\n", index, (int)((Bullet*)each->data)->Go->IsActive);
                break;
            }
            count++;
            each = next;
        }
        each = NULL;
        bullet_app = NULL;
    }
}

void RespawnEnemy(Enemy* enemy){
    if(enemy->Character_->Go->position->y >= HEIGHT_WINDOW - 90 || enemy->IsDead){
        enemy->Character_->Go->position->x = GetRandomInRange(100, WIDTH_WINDOW - (100 + enemy->Character_->Go->texture_size->Width));
        enemy->Character_->Go->position->y = -GetRandomInRange(enemy->Character_->Go->texture_size->Height, enemy->Character_->Go->texture_size->Height - 300);
        enemy->IsAlive = true;
        enemy->IsDead = false;
        enemy->Character_->Go->IsActive = true;
        enemy->Character_->Hp = 50;
        //printf("enemy rispawnato!\n");
    }
}

void DestroyEnemy(Enemy* e){
    DestroyCharacter(e->Character_);
    Mix_FreeChunk(e->explosion);
    Mix_FreeChunk(e->shoot);
    free(e);
}

EnemyManager* NewEnemyManager(){
    EnemyManager* enemymgr = (EnemyManager*)calloc(1, sizeof(EnemyManager));
    enemymgr->enemys = NewList();
    return enemymgr;    
}

void DestroyEnemyManager(EnemyManager* enemymgr){
    Node* each = enemymgr->enemys->__head;
    while (each)
    {
        Node* next = each->next;
        DestroyEnemy(((Enemy*)each->data));
        each = next;
    }
    each = NULL;
    DestroyList(enemymgr->enemys);
    free(enemymgr);
}

void AddEnemyManagerList(EnemyManager* enemymgr, Size* s, char* txt_path, int score){
    AddElemList(enemymgr->enemys, NewEnemy(s, txt_path, score));
}

void UpdateEnemyManager(SDL_Renderer* renderer, EnemyManager* enemymgr, double dt){
    Node* each = enemymgr->enemys->__head;
    while (each)
    {
        Node* next = each->next;
        AI(((Enemy*)each->data), dt);
        UpdateEnemy(renderer, ((Enemy*)each->data), dt);
        each = next;
    }
    each = NULL;
}

void AI(Enemy* enemy, double dt){
    enemy->Character_->Go->position->y += enemy->Character_->Speed * dt;
}
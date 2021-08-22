#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"
#include "inputsystem.h"


typedef struct
{
    Character* Character_;
    int score;
    //float DelayShoot;
    float TimeShoot;
    boolean IsAlive;
    boolean IsDead;
    Mix_Chunk* shoot;
    Mix_Chunk* explosion;
} Enemy;

typedef struct
{
    List* enemys;
} EnemyManager;


// ENEMY MANAGER
EnemyManager* NewEnemyManager();
void AddEnemyManagerList(EnemyManager* enemymgr, Size* s, char* txt_path, int score);
void UpdateEnemyManager(SDL_Renderer* renderer, EnemyManager* enemymgr, double dt);
void DestroyEnemyManager(EnemyManager* enemymgr);

// ENEMY
Enemy* NewEnemy(Size* s, char* texture, int score);
void UpdateEnemy(SDL_Renderer* renderer, Enemy* enemy, double dt);
void RespawnEnemy(Enemy* enemy);
void ShootEnemy(Enemy* enemy, double dt);
void ShootEnemyBullets(Enemy* e);
void AI(Enemy* enemy, double dt);
void DestroyEnemy(Enemy* e);



#endif // ENEMY_H
#include "physics.h"

PhysicsManager* NewPhysicsManager(Player* p, EnemyManager* enemymgr){
    PhysicsManager* pm = (PhysicsManager*)calloc(1, sizeof(PhysicsManager));
    pm->player = p;
    pm->enemymgr = enemymgr;
    return pm;
}

void DestroyPhysicsManager(PhysicsManager* pm){
    free(pm);
}

void CheckCollision(PhysicsManager* pm){
    CheckCollisionPlayerEnemy(pm);
    CheckCollisionPlayerBullets(pm);
    CheckCollisionEnemyBullets(pm);
}

void CheckCollisionPlayerEnemy(PhysicsManager* pm){
    Player* player = pm->player;
    Node* each = pm->enemymgr->enemys->__head;
    Enemy* enemy;
    while (each)
    {
        Node* next = each->next;
        enemy = (Enemy*)each->data;
        if (player->IsAlive && enemy->IsAlive)
        {
            if(CheckCollisionPoint(player->Character_->Go, enemy->Character_->Go)){
                //printf("collisione player_to_enemy\n");
                int player_hp = player->Character_->Hp;
                player->Character_->Hp -= enemy->Character_->Hp;
                enemy->Character_->Hp -= player_hp;
                player->score += enemy->score;
                break;
            }
        }
        each = next;
    }
    enemy = NULL;
    each = NULL;
    player = NULL;
}

void CheckCollisionEnemyBullets(PhysicsManager* pm){
    Node* each = pm->enemymgr->enemys->__head;
    Enemy* enemy;
    while (each)
    {
        Node* next = each->next;
        enemy = (Enemy*)each->data;
        if (enemy->IsAlive && !enemy->IsDead && enemy->Character_->Go->position->y > 0)
        {
            CheckCollisionEnemyBulletsPlayer(pm->player, enemy);
            //CheckCollisionPlayerBulletEnemy(pm, bullet);
        }
        each = next;
    }
    enemy = NULL;
    each = NULL;
}

void CheckCollisionEnemyBulletsPlayer(Player* player, Enemy* enemy){
    Node* each = enemy->Character_->bullets->__head;
    Bullet* bullet;
    while (each)
    {
        Node* next = each->next;
        bullet = (Bullet*)each->data;
        if (bullet->Go->IsActive)
        {
            if(CheckCollisionPoint(player->Character_->Go, bullet->Go)){
                //printf("collision enemybullet_player\n");
                bullet->Go->IsActive = false;
                player->Character_->Hp -= bullet->Damage;
                break;
            }
        }
        each = next;
    }
    bullet = NULL;
    each = NULL;
}


void CheckCollisionPlayerBullets(PhysicsManager* pm){
    Node* each = pm->player->Character_->bullets->__head;
    Bullet* bullet;
    while (each)
    {
        Node* next = each->next;
        bullet = (Bullet*)each->data;
        if (bullet->Go->IsActive == true)
        {
            CheckCollisionPlayerBulletEnemy(pm, bullet);
        }
        each = next;
    }
    bullet = NULL;
    each = NULL;
}

void CheckCollisionPlayerBulletEnemy(PhysicsManager* pm, Bullet* bullet){
    Node* each = pm->enemymgr->enemys->__head;
    Enemy* enemy;
    while (each)
    {
        Node* next = each->next;
        enemy = (Enemy*)each->data;
        if (enemy->IsAlive && !enemy->IsDead && enemy->Character_->Go->position->y > 0)
        {
            if(CheckCollisionPoint(enemy->Character_->Go, bullet->Go)){
                //printf("collision playerbullet -> enemy\n");
                bullet->Go->IsActive = false;
                enemy->Character_->Hp -= bullet->Damage;
                if (enemy->Character_->Hp <= 0)
                {
                    pm->player->score += enemy->score;
                }
                break;
            }
        }
        each = next;
    }
    enemy = NULL;
    each = NULL;
}

boolean CheckCollisionPoint(GameObject* player, GameObject* enemy){
    Point* enemy_min = enemy->position;
    Point* enemy_max = GetMaxPointGameObject(enemy);
    // printf("\n\n--------------\nenemy_min x: %f y: %f \n", enemy_min->x, enemy_min->y);
    // printf("enemy_max x: %f y: %f \n--------------\n\n", enemy_max->x, enemy_max->y);
    if (PointInRect(enemy_min, player) || PointInRect(enemy_max, player) || PointInRect(NewPoint(enemy_max->x, enemy_min->y), player) || PointInRect(NewPoint(enemy_min->x, enemy_max->y), player))
    {
        enemy_max = NULL;
        enemy_min = NULL;
        return true;
    }
    else {
        enemy_max = NULL;
        enemy_min = NULL;
        return false;
    }
}

boolean PointInRect(Point* p, GameObject* go){
    Point* min = go->position;
    Point* max = GetMaxPointGameObject(go);
    // printf("bullet_min x: %f y: %f \n", min->x, min->y);
    // printf("bullet_max x: %f y: %f \n", max->x, max->y);
    if (p->x >= min->x && p->y >= min->y)
    {
        if (p->x <= max->x && p->y <= max->y)
        {
            max = NULL;
            min = NULL;
            return true;
        }
        else{
            max = NULL;
            min = NULL;
            return false;
        }
    }
    else{
        max = NULL;
        min = NULL;
        return false;
    }
}

Point* GetMaxPointGameObject(GameObject* go){
    return NewPoint(go->position->x + go->texture_size->Width, go->position->y + go->texture_size->Height);
}
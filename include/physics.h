#ifndef PHYSICS_H
#define PHYSICS_H

#include <common.h>
#include <player.h>
#include <enemy.h>

typedef struct
{
    Player* player;
    EnemyManager* enemymgr;
} PhysicsManager;

PhysicsManager* NewPhysicsManager(Player* p, EnemyManager* enemymgr);
void DestroyPhysicsManager(PhysicsManager* pm);

// PRIMARY
void CheckCollision(PhysicsManager* pm);
Point* GetMaxPointGameObject(GameObject* go);
boolean CheckCollisionPoint(GameObject* go1, GameObject* go2);
boolean PointInRect(Point* p, GameObject* go);

// ENEMY <=> PLAYER
void CheckCollisionPlayerEnemy(PhysicsManager* pm);

// PLAYER_BULLET -> ENEMY
void CheckCollisionPlayerBullets(PhysicsManager* pm);
void CheckCollisionPlayerBulletEnemy(PhysicsManager* pm, Bullet* bullet);

// ENEMY_BULLET -> PLAYER
void CheckCollisionEnemyBullets(PhysicsManager* pm);
void CheckCollisionEnemyBulletsPlayer(Player* player, Enemy* enemy);

#endif // PHYSICS_H
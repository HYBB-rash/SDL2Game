#ifndef SNAKE_BULLET_H_
#define SNAKE_BULLET_H_

#include "types.h"
#include "weapon.h"
#include "player.h"

/**
 * 子弹
 */
class Bullet{
public:
    Weapon* parent;
    int x, y, team;
    Snake* owner;
    double rad; // 角度
    Animation* ani;
} ;
Bullet* createBullet(Snake* owner,Weapon* parent, int x, int y, double rad, int team, Animation* ani);
void destroyBullet(Bullet* bullet);
void moveBullet(Bullet* bullet);

#endif

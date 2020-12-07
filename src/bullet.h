//
// Created by hyong on 2020/12/7.
//

#ifndef SDL2GAME_BULLET_H
#define SDL2GAME_BULLET_H
#include "types.h"
#include "weapon.h"
#include "player.h"
// 子弹
class Bullet{
public:
    Weapon* parent;
    int x, y, team;
    Snake* owner;
    double rad; // 角度
    Animation* ani;
};
Bullet* createBullet(Snake* owner,Weapon* parent, int x, int y, double rad, int team, Animation* ani);
void destroyBullet(Bullet* bullet);
void moveBullet(Bullet* bullet);
#endif //SDL2GAME_BULLET_H

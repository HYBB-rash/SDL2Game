//
// Created by hyong on 2020/12/8.
//

#include "bullet.h"
#include "helper.h"

Bullet *createBullet(Snake *owner, Weapon *parent, int x, int y, double rad, int team, Animation *ani){
    auto *bullet = new Bullet();
    *bullet = (Bullet){parent, x, y, team, owner, rad, new Animation()};
    bullet->ani->x = x;
    bullet->ani->y = y;
    bullet->ani->angle = rad * 180 / PI;
    return bullet;
}

void destroyBullet(Bullet* bullet){
    free(bullet);
}

void moveBullet(Bullet* bullet){
    int speed = bullet->parent->bulletSpeed;
    bullet->x += cos(bullet->rad) * speed;
    bullet->y += sin(bullet->rad) * speed;
    bullet->ani->x = bullet->x;
    bullet->ani->y = bullet->y;
}
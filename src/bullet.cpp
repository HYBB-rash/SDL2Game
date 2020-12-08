#include "bullet.h"

#include "helper.h"

Bullet* createBullet(Snake* owner, Weapon* parent, int x, int y, double rad,
                     int team, Animation* ani) {
    auto* bullet = static_cast<Bullet *>(malloc(sizeof(Bullet)));
    *bullet = (Bullet){parent, x, y, team, owner, rad, static_cast<Animation *>(malloc(sizeof(Animation)))};
    copyAnimation(ani, bullet->ani);
    bullet->ani->x = x;
    bullet->ani->y = y;
    bullet->ani->angle = rad * 180 / PI;
    return bullet;
}
/**
 * 计算子弹的下一刻位置并移动到下一时刻的坐标
 * @param bullet 待计算的子弹
 */
void moveBullet(Bullet* bullet) {
    int speed = bullet->parent->bulletSpeed;
    bullet->x += cos(bullet->rad) * speed;
    bullet->y += sin(bullet->rad) * speed;
    bullet->ani->x = bullet->x;
    bullet->ani->y = bullet->y;
}
void destroyBullet(Bullet* bullet) { free(bullet); }

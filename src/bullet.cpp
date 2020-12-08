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

void Bullet::moveBullet() {
    int speed = parent->bulletSpeed;
    x += cos(rad) * speed;
    y += sin(rad) * speed;
    ani->x = x;
    ani->y = y;
}
void Bullet::destroyBullet() { delete(this); }

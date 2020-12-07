//
// Created by hyong on 2020/12/7.
//

#include "sprite.h"
#include "render.h"

#include <cstdlib>
#include <cstring>

void Sprite::initSprite(Sprite *model, int x, int y) {
    memcpy(this, model, sizeof (Sprite));
    this->x = x;
    this->y = y;
    this->bufferSize = 0;
    auto *ani = new Animation();
    copyAnimation(model->ani, ani);
    this->ani = ani;
}

Sprite* createSprite(Sprite* model, int x, int y){
    auto *self = new Sprite();
    self->initSprite(model, x, y);
    return self;
}


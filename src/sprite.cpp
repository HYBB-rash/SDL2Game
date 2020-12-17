#include "sprite.h"

#include "render.h"

#include <cstdlib>
#include <cstring>

void Sprite::initSprite(Sprite *model, int x, int y) {
    memcpy(this, model, sizeof(Sprite));
    this->x = x;
    this->y = y;
    this->bufferSize = 0;
    auto* ani = new Animation();
    copyAnimation(model->ani, ani);
    this->ani = ani;
    updateAnimationOfSprite(this);
}
Sprite* createSprite(Sprite* model, int x, int y) {
    auto* self = static_cast<Sprite *>(malloc(sizeof(Sprite)));
    self->initSprite(model, x, y);
    return self;
}

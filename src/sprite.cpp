#include "sprite.h"

#include "render.h"

#include <stdlib.h>
#include <string.h>

void Sprite::initSprite(Sprite *model, int x, int y) {
    memcpy(this, model, sizeof(Sprite));
    this->x = x;
    this->y = y;
    this->bufferSize = 0;
    auto* ani = static_cast<Animation *>(malloc(sizeof(Animation)));
    copyAnimation(model->ani, ani);
    this->ani = ani;
    updateAnimationOfSprite(this);
}
Sprite* createSprite(Sprite* model, int x, int y) {
    auto* self = static_cast<Sprite *>(malloc(sizeof(Sprite)));
    self->initSprite(model, x, y);
    return self;
}

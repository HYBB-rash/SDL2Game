#ifndef SNAKE_SPRITE_H_
#define SNAKE_SPRITE_H_

#include "types.h"
#include "weapon.h"
#include "adt.h"

/**
 *
 */
class PositionBuffer{
public:
    int x, y;
    Direction direction;
} ;

/**
 * 精灵（人物）数据结构
 */
class Sprite{
public:
    int x, y, hp, totoalHp;   // 位置，血量，血量上限
    Weapon* weapon;           // 武器
    Animation* ani;
    Direction face;
    Direction direction;
    PositionBuffer buffer[POSITION_BUFFER_SIZE];
    int bufferSize;
    int lastAttack;
    double dropRate;

    void initSprite(Sprite *model, int x, int y);
} ;

void changeSpriteDirection(LinkNode*, Direction);

Sprite* createSprite(Sprite* model, int x, int y);

#endif

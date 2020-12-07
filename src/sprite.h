//
// Created by hyong on 2020/12/7.
//

#ifndef SDL2GAME_SPRITE_H
#define SDL2GAME_SPRITE_H
#include "types.h"
#include "weapon.h"
#include "adt.h"

/**
 *
 */
class PositionBuffer{
    int x, y;
    Direction direction;
} ;

/**
 * 精灵（人物）数据结构
 */
class Sprite{
    int x, y, hp, totoalHp;   // 位置，血量，血量上限
    Weapon* weapon;           // 武器
    Animation* ani;           // TODO
    Direction face;           // TODO
    Direction direction;      // TODO
    PositionBuffer buffer[POSITION_BUFFER_SIZE];// TODO
    int bufferSize;           // TODO
    int lastAttack;           // todo
    double dropRate;          // todo
} ;

void changeSpriteDirection(LinkNode*, Direction);
void initSprite(Sprite* model, Sprite* self, int x, int y);
Sprite* createSprite(Sprite* model, int x, int y);
#endif //SDL2GAME_SPRITE_H

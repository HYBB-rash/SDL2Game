#ifndef SNAKE_WEAPON_H_
#define SNAKE_WEAPON_H_

#include "types.h"

#define WEAPONS_SIZE 128

/**
 * 武器：剑
 */
#define WEAPON_SWORD 0

/**
 * 武器：魔兽之牙
 */
#define WEAPON_MONSTER_CLAW 1

/**
 * 武器（魔法）：火球
 */
#define WEAPON_FIREBALL 2

/**
 * 武器（魔法）：雷电
 */
#define WEAPON_THUNDER 3

/**
 * 武器（魔法）：弓箭
 */
#define WEAPON_ARROW 4

/**
 * 武器：魔兽之牙2
 */
#define WEAPON_MONSTER_CLAW2 5

/**
 * 武器：飞斧
 */
#define WEAPON_THROW_AXE 6

/**
 * 武器：一群飞斧
 */
#define WEAPON_MANY_AXES 7

/**
 * 武器：怪物的口水（带减速效果）
 */
#define WEAPON_SOLID 8

/**
 * 武器：怪物的口水
 */
#define WEAPON_SOLID_GREEN 9

#define WEAPON_ICEPICK 10
#define WEAPON_FIRE_SWORD 11
#define WEAPON_ICE_SWORD 12
#define WEAPON_HOLY_SWORD 13
#define WEAPON_PURPLE_BALL 14
#define WEAPON_PURPLE_STAFF 15
#define WEAPON_THUNDER_STAFF 16
#define WEAPON_SOLID_CLAW 17
#define WEAPON_POWERFUL_BOW 18

typedef enum {
    WEAPON_SWORD_POINT,
    WEAPON_SWORD_RANGE,
    WEAPON_GUN_RANGE,
    WEAPON_GUN_POINT,
    WEAPON_GUN_POINT_MULTI,
} WeaponType;
class WeaponBuff{
public:
    double chance;
    int duration;
} ;
class Weapon{
public:
    WeaponType wp;
    int shootRange, effectRange, damage, gap, bulletSpeed;
    Animation *birthAni, *deathAni, *flyAni;
    int birthAudio, deathAudio;
    WeaponBuff effects[BUFF_END];
} ;

void initWeapons();

#endif

#include "weapon.h"

#include "render.h"
#include "res.h"
#include "types.h"

#include <stdio.h>

extern Texture textures[RES_HALO_EXPLOSION2];
extern Mix_Chunk* sounds[AUDIO_SOUND_SIZE];

Weapon weapons[WEAPONS_SIZE];

/**
 * 初始化武器，为其创建在游戏中的动画
 * 如果在initWeapons未指定初始化属性值，则默认:
 * @param 攻击距离 32*2
 * @param 攻击范围为 40
 * @param 伤害为 10
 * @param 攻击间隔时间为 60
 * @param 射速为 6
 *
 * @param self 武器
 * @param birthTextureId 武器刷新是的贴图ID
 * @param deathTextureId 武器销毁时的贴图ID
 * @param flyTextureId 武器在飞行（远程攻击）时的贴图ID
 */
void initWeapon(Weapon* self, int birthTextureId, int deathTextureId, int flyTextureId) {
    Animation* birthAni = NULL;
    Animation* deathAni = NULL;
    Animation* flyAni = NULL;
    if (birthTextureId != -1) {
        birthAni = createAnimation(&textures[birthTextureId], NULL, LOOP_ONCE,
                                   SPRITE_ANIMATION_DURATION, 0, 0, SDL_FLIP_NONE,
                                   0, AT_CENTER);
    }
    if (deathTextureId != -1) {
        deathAni = createAnimation(&textures[deathTextureId], NULL, LOOP_ONCE,
                                   SPRITE_ANIMATION_DURATION, 0, 0, SDL_FLIP_NONE,
                                   0, AT_BOTTOM_CENTER);
    }
    if (flyTextureId != -1) {
        flyAni = createAnimation(&textures[flyTextureId], NULL, LOOP_INFI,
                                 SPRITE_ANIMATION_DURATION, 0, 0, SDL_FLIP_NONE, 0,
                                 AT_CENTER);
    }
    *self = (Weapon){
            WEAPON_SWORD_POINT, 32 * 2, 40, 10, 60, 6, birthAni, deathAni, flyAni, -1,
            AUDIO_CLAW_HIT};
}

/**
 * 初始化各类武器
 *
 */
void initWeapons() {
    Weapon* now;

    /**
     * 武器：剑
     * 攻击范围：32*3
     * 攻击伤害：30
     */
    initWeapon(now = &weapons[WEAPON_SWORD], -1, RES_SwordFx, -1);
    now->damage = 30;
    now->shootRange = 32 * 3;
    now->deathAni->scaled = false;
    now->deathAni->angle = -1;
    now->deathAudio = AUDIO_SWORD_HIT;

    /**
     * 武器：魔兽之牙
     * 射程：32*3+16
     * 攻击伤害：24
     * 武器类型：狂战斧
     * todo
     */
    initWeapon(now = &weapons[WEAPON_MONSTER_CLAW], -1, RES_CLAWFX2, -1);
    now->wp = WEAPON_SWORD_RANGE;
    now->shootRange = 32 * 3 + 16;
    now->damage = 24;
    now->deathAni->angle = -1;
    now->deathAni->at = AT_CENTER;
    now->deathAudio = AUDIO_CLAW_HIT_HEAVY;

    /**
     * 武器：火球
     * 射程：32*3+16
     * 攻击伤害：24
     * 武器类型：溅射枪
     * todo
     */
    initWeapon(now = &weapons[WEAPON_FIREBALL], RES_Shine, RES_HALO_EXPLOSION1,
               RES_FIREBALL);
    now->wp = WEAPON_GUN_RANGE;
    now->damage = 45;
    now->effectRange = 50;
    now->shootRange = 256;
    now->gap = 180;
    now->deathAni->angle = -1;
    now->deathAni->at = AT_CENTER;
    now->birthAni->duration = 24;
    now->birthAudio = AUDIO_SHOOT;
    now->deathAudio = AUDIO_FIREBALL_EXP;

    /**
     * 武器：雷电
     * 射程：128
     * 伤害：80
     * 攻击间隔：120
     * 武器类型：狂战斧类型
     * todo
     */
    initWeapon(now = &weapons[WEAPON_THUNDER], RES_BLOOD_BOUND, RES_Thunder, -1);
    now->wp = WEAPON_SWORD_RANGE;
    now->damage = 80;
    now->shootRange = 128;
    now->gap = 120;
    now->deathAni->angle = -1;
    now->deathAni->scaled = false;
    now->deathAudio = AUDIO_THUNDER;

    /**
     * 武器：落雷群
     * 射程：128
     * 伤害：50
     * 攻击间隔：120
     * 武器类型：狂战斧类型
     * todo
     */
    initWeapon(now = &weapons[WEAPON_THUNDER_STAFF], -1, RES_THUNDER_YELLOW, -1);
    now->wp = WEAPON_SWORD_RANGE;
    now->damage = 50;
    now->shootRange = 128;
    now->gap = 120;
    now->deathAni->angle = -1;
    now->deathAni->scaled = false;
    now->deathAudio = AUDIO_THUNDER;

    /**
     * 武器：弓箭
     * 射程：200
     * 伤害：10
     * 攻击间隔：40
     * 攻击物飞行速度：10
     * todo
     */
    initWeapon(now = &weapons[WEAPON_ARROW], -1, RES_HALO_EXPLOSION2, RES_ARROW);
    now->wp = WEAPON_GUN_POINT;
    now->gap = 40;
    now->damage = 10;
    now->shootRange = 200;
    now->bulletSpeed = 10;
    now->deathAni->angle = -1;
    now->deathAni->at = AT_CENTER;
    now->flyAni->scaled = false;
    now->birthAudio = AUDIO_LIGHT_SHOOT;
    now->deathAudio = AUDIO_ARROW_HIT;

    /**
     * 武器：强力弓
     * 射程：320
     * 伤害：25
     * 攻击间隔：60
     * 攻击物飞行速度：7
     * todo
     */
    initWeapon(now = &weapons[WEAPON_POWERFUL_BOW], -1, RES_HALO_EXPLOSION2,
               RES_ARROW);
    now->wp = WEAPON_GUN_POINT;
    now->gap = 60;
    now->damage = 25;
    now->shootRange = 320;
    now->bulletSpeed = 7;
    now->deathAni->angle = -1;
    now->deathAni->at = AT_CENTER;
    now->birthAudio = AUDIO_LIGHT_SHOOT;
    now->deathAudio = AUDIO_ARROW_HIT;
    now->effects[BUFF_ATTACK] = (WeaponBuff){0.5, 240};

    /**
     * 武器：魔兽之牙2
     * 暂未设计
     */
    initWeapon(now = &weapons[WEAPON_MONSTER_CLAW2], -1, RES_CLAWFX, -1);

    /**
     * 武器：飞斧
     * 射程：160
     * 伤害：12
     * 攻击物飞行速度：10
     * todo
     */
    initWeapon(now = &weapons[WEAPON_THROW_AXE], -1, RES_CROSS_HIT, RES_AXE);
    now->wp = WEAPON_GUN_POINT;
    now->damage = 12;
    now->shootRange = 160;
    now->bulletSpeed = 10;
    now->flyAni->duration = 24;
    now->flyAni->angle = -1;
    now->flyAni->scaled = false;
    now->deathAni->scaled = false;
    now->deathAni->at = AT_CENTER;
    now->birthAudio = AUDIO_LIGHT_SHOOT;
    now->deathAudio = AUDIO_ARROW_HIT;

    /**
     * 武器：飞斧群
     * 射程：180
     * 伤害：50
     * 攻击间隔：70
     * 影响范围：50
     * 攻击物飞行速度：4
     * todo
     */
    initWeapon(now = &weapons[WEAPON_MANY_AXES], -1, RES_CROSS_HIT, RES_AXE);
    now->wp = WEAPON_GUN_POINT_MULTI;
    now->shootRange = 180;
    now->gap = 70;
    now->effectRange = 50;
    now->damage = 50;
    now->bulletSpeed = 4;
    now->flyAni->duration = 24;
    now->flyAni->angle = -1;
    now->deathAni->at = AT_CENTER;
    now->birthAudio = AUDIO_LIGHT_SHOOT;
    now->deathAudio = AUDIO_ARROW_HIT;

    /**
     * 武器：污泥
     * buffer效果：减速
     * todo
     */
    initWeapon(now = &weapons[WEAPON_SOLID], -1, RES_SOLIDFX, -1);
    now->deathAni->scaled = false;
    now->deathAni->angle = -1;
    now->effects[BUFF_SLOWDOWN] = (WeaponBuff){0.3, 180};

    /**
     * 武器：污泥（绿色）
     * 射程：96
     * todo
     */
    initWeapon(now = &weapons[WEAPON_SOLID_GREEN], -1, RES_SOLID_GREENFX, -1);
    now->shootRange = 96;
    now->deathAni->scaled = false;
    now->deathAni->angle = -1;
    now->effects[BUFF_SLOWDOWN] = (WeaponBuff){0.3, 180};

    /**
     * 武器：todo
     */
    initWeapon(now = &weapons[WEAPON_SOLID_CLAW], -1, RES_SOLID_GREENFX, -1);
    now->wp = WEAPON_SWORD_RANGE;
    now->shootRange = 32 * 3 + 16;
    now->damage = 35;
    now->deathAni->scaled = false;
    now->deathAni->angle = -1;
    now->deathAudio = AUDIO_CLAW_HIT_HEAVY;
    now->effects[BUFF_SLOWDOWN] = (WeaponBuff){0.7, 60};

    /**
     * 武器：冰锥
     * 射程：256
     * 伤害：30
     * 攻击间隔：180
     * 攻击物飞行速度：8
     * 武器类型：溅射枪
     * 武器buff：减速
     * todo
     */
    initWeapon(now = &weapons[WEAPON_ICEPICK], -1, RES_ICESHATTER, RES_ICEPICK);
    now->wp = WEAPON_GUN_RANGE;
    now->damage = 30;
    now->effectRange = 50;
    now->shootRange = 256;
    now->gap = 180;
    now->bulletSpeed = 8;
    now->deathAni->angle = -1;
    now->flyAni->scaled = false;
    now->deathAni->at = AT_CENTER;
    now->effects[BUFF_FROZEN] = (WeaponBuff){0.2, 60};
    now->birthAudio = AUDIO_ICE_SHOOT;

    /**
     * 武器：魔法球
     * 射程：256
     * 伤害；20
     * 攻击间隔：100
     * 攻击物飞行速度：6
     * todo
     */
    initWeapon(now = &weapons[WEAPON_PURPLE_BALL], -1, RES_PURPLE_EXP,
               RES_PURPLE_BALL);
    now->wp = WEAPON_GUN_RANGE;
    now->damage = 20;
    now->effectRange = 50;
    now->shootRange = 256;
    now->gap = 100;
    now->bulletSpeed = 6;
    now->deathAni->angle = -1;
    now->deathAni->scaled = false;
    now->flyAni->scaled = false;
    now->deathAni->at = AT_CENTER;
    now->birthAudio = AUDIO_ICE_SHOOT;
    now->deathAudio = AUDIO_ARROW_HIT;

    /**
     * 武器：魔法球群
     * 射程：256
     * 伤害：45
     * 攻击间隔：100
     * 攻击物飞行速度：7
     * 影响范围：50
     * todo
     */
    initWeapon(now = &weapons[WEAPON_PURPLE_STAFF], -1, RES_PURPLE_EXP,
               RES_PURPLE_BALL);
    now->wp = WEAPON_GUN_POINT_MULTI;
    now->damage = 45;
    now->effectRange = 50;
    now->shootRange = 256;
    now->gap = 100;
    now->bulletSpeed = 7;
    now->deathAni->angle = -1;
    now->deathAni->scaled = false;
    now->flyAni->scaled = false;
    now->deathAni->at = AT_CENTER;
    now->birthAudio = AUDIO_ICE_SHOOT;
    now->deathAudio = AUDIO_ARROW_HIT;

    /**
     * 武器：圣剑
     * 射程：32*4
     * 伤害：30
     * 武器类型：狂战斧
     * 武器buff：
     */
    initWeapon(now = &weapons[WEAPON_HOLY_SWORD], -1, RES_GOLDEN_CROSS_HIT, -1);
    now->wp = WEAPON_SWORD_RANGE;
    now->damage = 30;
    now->shootRange = 32 * 4;
    now->effects[BUFF_DEFFENCE] = (WeaponBuff){0.6, 180};

    /**
     * 武器：冰剑
     * 射程：32*3.5
     * 伤害：80
     * 攻击间隔：30
     * 武器buff：减速
     */
    initWeapon(now = &weapons[WEAPON_ICE_SWORD], -1, RES_ICESHATTER, -1);
    now->wp = WEAPON_SWORD_RANGE;
    now->shootRange = 32 * 3 + 16;
    now->damage = 80;
    now->gap = 30;
    now->deathAni->angle = -1;
    now->deathAni->at = AT_CENTER;
    now->effects[BUFF_FROZEN] = (WeaponBuff){0.6, 80};
    now->deathAudio = AUDIO_SWORD_HIT;

#ifdef DBG
    puts("weapon done");
#endif
}

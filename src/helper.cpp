//
// Created by hyong on 2020/12/8.
//
#include "helper.h"

#include <cstdio>
#include <cstdlib>

#include "game.h"
#include "prng.h"
#include "res.h"
#include "types.h"

extern const int SCALLING_FACTOR;
extern Texture textures[];

int randInt(int l, int r){
    return prngRand() % (r - l + 1) + 1;
}

double randDouble() {
    return (double) prngRand() / PRNG_MAX;
}

bool inr(int x, int l, int r) {
    return x <= r && l <= x;
}

bool IntervalCross(int l1, int l2, int r1, int r2) {
    return MAX(l1, l2) < MIN(r1, r2);
}

bool RectRectCross(SDL_Rect *a, SDL_Rect *b) {
    return RectRectCalc(a, b) >= HELPER_RECT_CROSS_LIMIT;
}

bool RectCirCross(SDL_Rect *a, int x, int y, int r) {
    if (inr(x, a->x, a->x + a->w) && inr(y, a->y, a->y + a->h)) {
        puts("failed1");
        return true;
    }
    if (abs(x - a->x) <= r) {
        puts("failed2");
        return true;
    }
    if (abs(x - a->x - a->w) <= r) {
        puts("failed3");
        return true;
    }
    if (abs(y - a->y) <= r) {
        puts("failed4");
        return true;
    }
    if (abs(y - a->y - a->h) <= r) {
        puts("failed5");
        return true;
    }
    return false;
}

SDL_Rect getSpriteBoundBox(Sprite* sprite){
    Animation* ani = sprite->ani;
    SDL_Rect dst = {ani->x - ani->origin->width * SCALLING_FACTOR / 2,
                    ani->y - ani->origin->height * SCALLING_FACTOR,
                    ani->origin->width * SCALLING_FACTOR,
                    ani->origin->height * SCALLING_FACTOR};
    bool big = false;
    if (ani->origin == &textures[RES_BIG_DEMON])
        big = true;
    else if (ani->origin == &textures[RES_BIG_ZOMBIE])
        big = true;
    else if (ani->origin == &textures[RES_ORGRE])
        big = true;
    if (big) {
        dst.w -= BIG_SPRITE_EFFECT_DELTA;
        dst.x += BIG_SPRITE_EFFECT_DELTA / 2;
        dst.y += SPRITE_EFFECT_VERTICAL_DELTA;
        dst.h -= SPRITE_EFFECT_VERTICAL_DELTA;
    } else {
        dst.w -= SPRITE_EFFECT_DELTA;
        dst.x += SPRITE_EFFECT_DELTA / 2;
        dst.y += SPRITE_EFFECT_VERTICAL_DELTA;
        dst.h -= SPRITE_EFFECT_VERTICAL_DELTA;
    }
    return dst;
}

SDL_Rect getSpriteFeetBox(Sprite* sprite){
    Animation *ani = sprite->ani;
    SDL_Rect dst = getSpriteBoundBox(sprite);
    dst.y = ani->y - SPRITE_EFFECT_FEET;
    dst.h = SPRITE_EFFECT_FEET;
    return dst;
}

SDL_Rect getMapRect(int x, int y) {
    SDL_Rect ret = {x * UNIT, y * UNIT, UNIT, UNIT};
    return ret;
}

SDL_Rect getSpriteAnimationBox(Sprite *sprite) {
    Animation* ani = sprite->ani;
    SDL_Rect dst = {ani->x - ani->origin->width * SCALLING_FACTOR / 2,
                    ani->y - ani->origin->height * SCALLING_FACTOR,
                    ani->origin->width * SCALLING_FACTOR,
                    ani->origin->height * SCALLING_FACTOR};
    return dst;
}

int RectRectCalc(SDL_Rect* a, SDL_Rect* b){
    return RectRectCalc(a, b) >= HELPER_RECT_CROSS_LIMIT;
}

double distance(Point a, Point b){
    double dx = a.x - b.x, dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}
//
// Created by hyong on 2020/12/7.
//

#include <SDL.h>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>

#include "render.h"
#include "ai.h"
#include "game.h"
#include "helper.h"
#include "res.h"
#include "types.h"

#ifdef DBG
#include <cassert>
#endif

Snake *spriteSnake[SPRITES_MAX_NUM];
int spritesCount;
int playersCount;
extern Effect effects[];
SDL_Color BLACK;
SDL_Color WHITE;

const int SCALLING_FACTOR = 2;
int texturesCount;
Texture textures[TEXTURES_SIZE];
int textsCount;
Text texts[TEXTSET_SIZE];
Text* stageText;
Text* taskText;
Text* scoresText[MAX_PALYERS_NUM];

unsigned long long renderFrames;

LinkList animationsList[ANIMATION_LINK_LIST_NUM];
Animation* countDownBar;

void renderText(const Text* text, int x, int y, double scale){
    SDL_Rect dst = {x, y, lround(text->width * scale + 0.5),
                    lround(text->height * scale + 0.5)};
    SDL_RenderCopy(renderer, text->origin, nullptr, &dst);
}

SDL_Point renderCenteredText(const Text* text, int x, int y, double scale){
    int width = lround(text->width * scale + 0.5);
    int height = lround(text->height * scale + 0.5);
    SDL_Rect dst = {x - width / 2, y - height / 2, width, height};
    SDL_RenderCopy(renderer, text->origin, nullptr, &dst);
    return (SDL_Point) {x - width / 2, y - height / 2};
}

void setEffect(Texture *texture, Effect *effect) {
    if (!effect) return;
    SDL_SetTextureBlendMode(texture->origin, effect->mode);

    double interval = effect->duration / (effect->length - 1);
    double progress = effect->currentFrame;
    int stage = progress / interval;
    progress -= stage * interval;
    progress /= interval;

    SDL_Color mixed, prev = effect->keys[stage],
    nxt = effect->keys[MIN(stage + 1, effect->length - 1)];
    mixed.a = prev.a * (1 - progress) + nxt.a * progress;
    mixed.r = prev.r * (1 - progress) + nxt.r * progress;
    mixed.g = prev.g * (1 - progress) + nxt.g * progress;
    mixed.b = prev.b * (1 - progress) + nxt.b * progress;

    SDL_SetTextureColorMod(texture->origin, mixed.r, mixed.g, mixed.b);
    SDL_SetTextureAlphaMod(texture->origin, mixed.a);
}

void unsetEffect(Texture *texture) {
    SDL_SetTextureBlendMode(texture->origin, SDL_BLENDMODE_BLEND);
    SDL_SetTextureColorMod(texture->origin, 255, 255, 255);
    SDL_SetTextureAlphaMod(texture->origin, 255);
}

Animation *
createAndPushAnimation(LinkList *list, Texture *texture, const Effect *effect, LoopType lp, int duration, int x, int y,
                       SDL_RendererFlip flip, double angle, At at) {
    Animation *ani = createAnimation(texture, effect, lp, duration, x, y, flip, angle, at);
    LinkNode *node = createLinkNode(ani);
    pushLinkNode(list, node);
    return ani;
}

void updateAnimationLinkList(LinkList *list) {
    LinkNode *p = list->head;
    while (p) {
        Animation *ani = (Animation*)p->element;
        LinkNode *nxt = p->nxt;
        ani->currentFrame++;
        ani->lifeSpan--;
        if (ani->effect) {
            ani->effect->currentFrame ++;
            ani->effect->currentFrame %= ani->effect->duration;
        }
        if (ani->lp == LOOP_ONCE) {
            if (ani->currentFrame == ani->duration) {
                ani->destroyAnimation();

            }
        }
    }
}

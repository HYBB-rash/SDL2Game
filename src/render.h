//
// Created by hyong on 2020/12/7.
//

#ifndef SDL2GAME_RENDER_H
#define SDL2GAME_RENDER_H
#include <SDL.h>
#include "types.h"
#include "player.h"
#include "sprite.h"

#define ANIMATION_LINK_LIST_NUM 16
#define RENDER_LIST_MAP_ID 0
#define RENDER_LIST_MAP_SPECIAL_ID 1
#define RENDER_LIST_MAP_ITEMS_ID 2
#define RENDER_LIST_DEATH_ID 3
#define RENDER_LIST_SPRITE_ID 4
#define RENDER_LIST_EFFECT_ID 5
#define RENDER_LIST_MAP_FOREWALL 6
#define RENDER_LIST_UI_ID 7
#define RENDER_BUFFER_SIZE (1 << 16)
#define RENDER_HP_BAR_HEIGHT 2
#define RENDER_HP_BAR_WIDTH 20
#define RENDER_COUNTDOWN_BAR_WIDTH 300
#define RENDER_COUNTDOWN_BAR_HEIGHT 10
#define SPRITE_ANIMATION_DURATION 30
#define RENDER_BG_COLOR 25,17,23
#define RENDER_BLACKOUT_DURATION 20
#define RENDER_DIM_DURATION 8
#define RENDER_TERM_COUNT 60
#define RENDER_GAMEOVER_DURATION 1

// UI
#define UI_COUNTDOWN_BAR_WIDTH 128

/**
 * 渲染字体
 * @param text 目标字体
 * @param x 渲染的位置
 * @param y 渲染的位置
 * @param scale 缩放程度
 */
void renderText(const Text* text, int x, int y, double);

/**
 * 将字体渲染在中间的位置
 * @param text 目标字符
 * @param x  位置
 * @param y  位置
 * @param scale  缩放倍率
 * @return 返回SDL_Point坐标
 */
SDL_Point renderCenteredText(const Text* text, int x, int y, double);


void setEffect(Texture* texture, Effect* effect);
void unsetEffect(Texture* texture);

/**
 * 将动画效果附着到链表中
 * @param list
 * @param texture
 * @param effect
 * @param lp
 * @param duration
 * @param x
 * @param y
 * @param flip
 * @param angle
 * @param at
 * @return
 */
Animation* createAndPushAnimation(LinkList* list, Texture* texture,
                                  const Effect* effect, LoopType lp,
                                  int duration, int x, int y,
                                  SDL_RendererFlip flip, double angle, At at);
void updateAnimationLinkList(LinkList* list);

/**
 * 渲染整个队列
 * @param list 等待渲染的队列
 */
void renderAnimationLinkList(LinkList* list);
void updateAnimationOfSprite(Sprite* self);
void updateAnimationOfSnake(Snake* snake);
void updateAnimationOfBlock(Block* self);
void updateAnimationFromBind(Animation* self);
void bindAnimationToSprite(Animation* ani, Sprite* sprite, bool isStrong);
void clearBindInAnimationsList(Sprite* sprite, int id);
void renderAnimation(Animation* ani);
void initRenderer();
void initCountDownBar();
void initInfo();
void clearRenderer();
void render();
void renderUi();
void pushAnimationToRender(int id, Animation* ani);
void blackout();
void dim();
#endif //SDL2GAME_RENDER_H

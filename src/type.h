//
// Created by hyong on 2020/12/6.
//

#ifndef SDL2GAME_TYPE_H
#define SDL2GAME_TYPE_H
#include <SDL.h>
#include <SDL_mixer.h>
#include <string>

#define TEXT_LEN 1024
#define POSITION_BUFFER_SIZE 256
#define BUFF_BEGIN 0
#define BUFF_FROZEN 0
#define BUFF_SLOWDOWN 1
#define BUFF_DEFFENCE 2
#define BUFF_ATTACK 3
#define BUFF_END 4

// Renderer Types
typedef enum {LEFT, RIGHT, UP, DOWN} Direction;
typedef enum {AT_TOP_LEFT, AT_BOTTOM_LEFT, AT_BOTTOM_CENTER, AT_CENTER} At;
typedef enum {LOOP_ONCE, LOOP_INFI, LOOP_LIFESPAN} LoopType;

// 渲染器的基本渲染类型
class Texture {
    SDL_Texture *origin;
    int height, width, frames;
    SDL_Rect *crops;
public:
    void initTexture(Texture *self, SDL_Texture *origin, int width, int height, int frames);
    void destroyTexture(Texture *self);
};

// 渲染字体的类型
class Text{
    std::string text;
    int height, width;
    SDL_Texture *origin;
    SDL_Color color;
public:
    static bool initText(Text *self, const std::string& str,  SDL_Color color);
    static Text* createText(const std::string&, SDL_Color sdlColor);
    void setText(Text *self, const std::string& str);
};

class Effect{
    int duration, currentFrame, length;
    SDL_Color *keys;
    SDL_BlendMode mode;
public:
    void initEffect(Effect* self, int duration, int length, SDL_BlendMode mode);
    void destroyEffect(Effect* self);
    void copyEffect(const Effect* src, Effect* dest);
};

class Animation{
    LoopType lp;
    Texture *origin;
    Effect *effect;
    int duration, currentFrame;
    int x, y;
    double angle;
    SDL_RendererFlip flip;
    At at;
    void *bind;
    bool scaled;
    bool strongBind;
    int lifeSpan;
public:
    void initAnimation(Animation* self, Texture* origin, const Effect* effect,LoopType lp, int duration, int x, int y,
                       SDL_RendererFlip flip, double angle, At at);
    static Animation* createAnimation(Texture* origin, const Effect* effect, LoopType lp, int duration, int x, int y,
                               SDL_RendererFlip flip, double angle, At at);
    void destroyAnimation(Animation* self);
    void copyAnimation(Animation* src, Animation* dest);
};

// Game Logic Types
class Point {
    int x, y;
};
class Score{
    int damage, stand, killed, got;
    double rank;
public:
    static Score* createScore();
    void calcScore(Score*);
    void addScore(Score*, Score*);
    void destroyScore(Score*);
};

typedef enum { BLOCK_TRAP, BLOCK_WALL, BLOCK_FLOOR, BLOCK_EXIT } BlockType;
class Block {
    BlockType bp;
    int x, y, bid;
    bool enable;
    Animation* ani;
};

typedef enum {
    ITEM_NONE,
    ITEM_HERO,
    ITEM_HP_MEDCINE,
    ITEM_HP_EXTRA_MEDCINE,
    ITEM_WEAPON
} ItemType;
class Item{
    ItemType type;
    int id, belong;
    Animation* ani;
} Item;
#endif //SDL2GAME_TYPE_H

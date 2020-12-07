//
// Created by hyong on 2020/12/7.
//

#ifndef SDL2GAME_TYPES_H
#define SDL2GAME_TYPES_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <cstdbool>
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

typedef enum { LEFT, RIGHT, UP, DOWN } Direction; // 枚举类型，分别指代上下左右
typedef enum { AT_TOP_LEFT, AT_BOTTOM_LEFT, AT_BOTTOM_CENTER, AT_CENTER } At;
typedef enum { LOOP_ONCE, LOOP_INFI, LOOP_LIFESPAN } LoopType;

class Texture{
public:
    SDL_Texture* origin;
    int height, width, frames;
    // SDL_Rect* crops;
    SDL_Rect* crops;

    void initTexture(SDL_Texture* origin, int width, int height, int frames);
    void destroyTexture();
};

class Text{
public:
    std::string text;
    int height, width;
    SDL_Texture* origin;
    SDL_Color color;

    void setText(std::string str);
    bool initText(std::string str, SDL_Color color);
    void destroyText();
};
Text* createText(std::string str, SDL_Color color);

class Effect{
public:
    int duration, currentFrame, length;
    SDL_Color* keys;
    SDL_BlendMode mode;

    void initEffect(int duration, int length, SDL_BlendMode mode);
    void destroyEffect();
} ;
void copyEffect(const Effect* src, Effect* dest);

class Animation{
public:
    LoopType lp;
    Texture* origin;
    Effect* effect;
    int duration, currentFrame;
    int x, y;
    double angle;
    SDL_RendererFlip flip;
    At at;
    void* bind;
    bool scaled;
    bool strongBind;
    int lifeSpan;

    void initAnimation(Texture* origin, const Effect* effect, LoopType lp, int duration, int x, int y,
                       SDL_RendererFlip flip, double angle, At at);
    void destroyAnimation();
} ;
Animation* createAnimation(Texture* origin, const Effect* effect, LoopType lp, int duration, int x, int y, SDL_RendererFlip flip,
                           double angle, At at);
void copyAnimation(Animation* src, Animation* dest);

// Game Logic Types
class Point{
public:
    int x, y;
} ;
class Score{
public:
    int damage, stand, killed, got;
    double rank;

    void calcScore();
    void destroyScore();
} ;

Score* createScore();
void addScore(Score*, Score*);


typedef enum { BLOCK_TRAP, BLOCK_WALL, BLOCK_FLOOR, BLOCK_EXIT } BlockType;
class Block{
public:
    BlockType bp;
    int x, y, bid;
    bool enable;
    Animation* ani;
} ;
typedef enum {
    ITEM_NONE,
    ITEM_HERO,
    ITEM_HP_MEDCINE,
    ITEM_HP_EXTRA_MEDCINE,
    ITEM_WEAPON
} ItemType;

class Item{
public:
    ItemType type;
    int id, belong;
    Animation* ani;
} ;
#endif //SDL2GAME_TYPES_H

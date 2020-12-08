#ifndef SNAKE_TYPES_
#define SNAKE_TYPES_
#include <SDL.h>
#include <SDL_mixer.h>
#include <stdbool.h>

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
} ;
class Text{
public:
    char text[TEXT_LEN];
    int height, width;
    SDL_Texture* origin;
    SDL_Color color;
} ;
void setText(Text* self, const char* str);
class Effect{
public:
    int duration, currentFrame, length;
    SDL_Color* keys;
    SDL_BlendMode mode;
} ;
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
} ;

void initTexture(Texture* self, SDL_Texture* origin, int width, int height,
                 int frames);
void destroyTexture(Texture* self);

bool initText(Text* self, const char* str, SDL_Color color);
Text* createText(const char* str, SDL_Color color);
void destroyText(Text* self);

void initEffect(Effect* self, int duration, int length, SDL_BlendMode mode);
void destroyEffect(Effect* self);
void copyEffect(const Effect* src, Effect* dest);

void initAnimation(Animation* self, Texture* origin, const Effect* effect,
                   LoopType lp, int duration, int x, int y,
                   SDL_RendererFlip flip, double angle, At at);
Animation* createAnimation(Texture* origin, const Effect* effect, LoopType lp,
                           int duration, int x, int y, SDL_RendererFlip flip,
                           double angle, At at);
void destroyAnimation(Animation* self);
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
} ;
Score* createScore();
void calcScore(Score*);
void addScore(Score*, Score*);
void destroyScore(Score*);
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
#endif

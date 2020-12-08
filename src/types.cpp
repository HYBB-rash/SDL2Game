#include "types.h"

#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "helper.h"
#include "render.h"

#ifdef DBG
#include <assert.h>
#endif

extern LinkList animationsList[];
extern TTF_Font* font;
extern SDL_Renderer* renderer;
SDL_Color BLACK = {0, 0, 0, 255};
SDL_Color WHITE = {255, 255, 255, 255};
void Texture::initTexture(SDL_Texture *origin, int width, int height, int frames) {
    this->origin = origin;
    this->width = width;
    this->height = height;
    this->frames = frames;
    this->crops = new SDL_Rect[frames];
    // self->crops = malloc(sizeof(SDL_Rect) * frames);
}
void Texture::destroyTexture() {
#ifdef DBG
    assert(self);
#endif
    delete(crops);
    delete(this);
}
bool Text::initText(const char *str, SDL_Color color) {
    color = color;
    strcpy(text, str);
    // Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, str, color);
    if (textSurface == nullptr) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n",TTF_GetError());
    } else {
        // Create texture from surface pixels
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        width = textSurface->w;
        height = textSurface->h;
        SDL_FreeSurface(textSurface);
        if (texture == nullptr) {
            printf("Unable to create texture from rendered text! SDL Error: %s\n",SDL_GetError());
        } else {
            origin = texture;
            return true;
        }
    }
    return false;
}
Text* createText(const char* str, SDL_Color color) {
    Text* self = new Text();
    self->initText(str, color);
    return self;
}
void Text::setText(const char *str) {
    if (!strcmp(str, text)) return;
    SDL_DestroyTexture(origin);
    initText(str, color);
}
void Text::destroyText() {
    SDL_DestroyTexture(origin);
    delete(this);
}
void Effect::initEffect(int duration, int length, SDL_BlendMode mode) {
    keys = new SDL_Color[length];
    this->duration = duration;
    this->length = length;
    this->currentFrame = 0;
    this->mode = mode;
}
// deep copy
void copyEffect(const Effect* src, Effect* dest) {
    memcpy(dest, src, sizeof(Effect));
    dest->keys = new SDL_Color[src->length];
    memcpy(dest->keys, src->keys, sizeof(SDL_Color) * src->length);
}
void Effect::destroyEffect() {
//    free(keys);
    delete(this);
}

void Animation::initAnimation(Texture *origin, const Effect *effect, LoopType lp, int duration, int x, int y,
                              SDL_RendererFlip flip,
                              double angle, At at) {
    // will deep copy effect
    this->origin = origin;
    if (effect) {
        this->effect = new Effect();
        copyEffect(effect, this->effect);
    } else this->effect = nullptr;
    this->lp = lp;
    this->duration = duration;
    this->currentFrame = 0;
    this->x = x;
    this->y = y;
    this->flip = flip;
    this->angle = angle;
    this->at = at;
    this->bind = nullptr;
    this->strongBind = false;
    this->scaled = true;
    this->lifeSpan = duration;
}
Animation* createAnimation(Texture* origin, const Effect* effect, LoopType lp,
                           int duration, int x, int y, SDL_RendererFlip flip,
                           double angle, At at) {
    auto* self = new Animation();
    self->initAnimation(origin, effect, lp, duration, x, y, flip, angle, at);
    return self;
}
void Animation::destroyAnimation() {
    effect->destroyEffect();
    delete(this);
}
void copyAnimation(Animation* src, Animation* dest) {
    memcpy(dest, src, sizeof(Animation));
    if (src->effect) {
        dest->effect = new Effect();
        copyEffect(src->effect, dest->effect);
    }
}

/**
 * 初始化链表的节点
 * @param self 一个链表节点
 */
void LinkNode::initLinkNode() {
    nxt = pre = static_cast<LinkNode *>(element = nullptr);
}

LinkNode* createLinkNode(void* element) {
    auto* self = new LinkNode();
    self->initLinkNode();
    self->element = element;
    return self;
}

/**
 * 初始化链表，把链表的头节点和尾节点初始化为null
 * @param self 一个链表
 */
void LinkList::initLinkList() { head = tail = nullptr; }

/**
 * 创建一个链表结构
 * @return 链表指针
 */
LinkList* createLinkList() {
    auto* self = new LinkList();
    self->initLinkList();
    return self;
}

void LinkList::pushLinkNodeAtHead(LinkNode *node) {
    if (head == nullptr) {
        head = tail = node;
    } else {
        node->nxt = head;
        head->pre = node;
        head = node;
    }
}
void LinkList::pushLinkNode(LinkNode *node) {
    if (head == nullptr) {
        head = tail = node;
    } else {
        tail->nxt = node;
        node->pre = tail;
        tail = node;
    }
}

/**
 * 删除链表中的节点
 * @param list
 * @param node
 */
void LinkList::removeLinkNode(LinkNode *node) {
    if (node->pre) node->pre->nxt = node->nxt;
    else head = node->nxt;
    if (node->nxt) node->nxt->pre = node->pre;
    else tail = node->pre;
    delete(node);
}

void LinkList::destroyLinkList() {
    for (LinkNode *p = head, *nxt; p; p = nxt) {
        nxt = p->nxt;
        delete(p);
    }
    delete(this);
}

/**
 * 将所有的链表的节点对应的动画效果删除，并每删除一个动画，就移除一个链表节点
 * @param list
 */
void destroyAnimationsByLinkList(LinkList* list) {
    for (LinkNode *p = list->head, *nxt; p; p = nxt) {
        nxt = p->nxt;
        static_cast<Animation *>(p->element)->destroyAnimation();
        list->removeLinkNode(p);
    }
}
void removeAnimationFromLinkList(LinkList* self, Animation* ani) {
    for (LinkNode* p = self->head; p; p = p->nxt)
        if (p->element == ani) {
            self->removeLinkNode(p);
            ani->destroyAnimation();
            break;
        }
}
void changeSpriteDirection(LinkNode* self, Direction newDirection) {
    auto* sprite = static_cast<Sprite *>(self->element);
    if (sprite->direction == (1 ^ newDirection)) return;
    sprite->direction = newDirection;
    if (newDirection == LEFT || newDirection == RIGHT)
        sprite->face = newDirection;
    if (self->nxt) {
        auto* nextSprite = static_cast<Sprite *>(self->nxt->element);
        nextSprite->buffer[nextSprite->bufferSize++] =
                (PositionBuffer){sprite->x, sprite->y, sprite->direction};
    }
}
void initScore(Score* score) { memset(score, 0, sizeof(Score)); }
Score* createScore() {
    auto* score = new Score();
    initScore(score);
    return score;
}
void Score::destroyScore() { delete(this); }
void Score::calcScore() {
    if (!got) {
        rank = 0;
        return;
    }
    extern int gameLevel;
    rank = (double)damage / got + (double)stand / got + got * 50 + killed * 100;
    rank *= gameLevel + 1;
}
void Score::addScore(Score *b) {
    got += b->got;
    damage += b->damage;
    killed += b->killed;
    stand += b->stand;
    calcScore();
}

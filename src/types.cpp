//
// Created by hyong on 2020/12/7.
//

#include "types.h"
#include <SDL_ttf.h>
#include <cstdlib>
#include <cstdbool>
#include <iostream>

#include "helper.h"
#include "render.h"

extern LinkList animationsList[];
TTF_Font* font;
SDL_Renderer* renderer;
SDL_Color BLACK = {0, 0, 0, 255};
SDL_Color WHITE = {255, 255, 255, 255};
#ifdef DGB
#include <cassert>
#endif
//LinkList animationList[];

void Texture::initTexture(SDL_Texture *origin, int width, int height, int frames) {
    this->origin = origin;
    this->width = width;
    this->height = height;
    this->frames = frames;
    this->crops = new SDL_Rect[frames];
}

void Texture::destroyTexture() {
#ifdef DBG
    assert(this);
#endif
    free(crops);
    free(this);
}

void Text::setText(std::string str) {
    if (this->text != str) return;
    SDL_DestroyTexture(this->origin);
    this->initText(str, color);
}

bool Text::initText(std::string str, SDL_Color color) {
    this->color = color;
    this->text = str;
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, str.c_str(), color);
    if (textSurface == nullptr)
        std::cout << "Unable to render text surface! SDL_ttf Error: "<< SDL_GetError() << std::endl;
    else {
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        width = textSurface->w;
        height = textSurface->h;
        SDL_FreeSurface(textSurface);
        if (texture == nullptr)
            std::cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << std::endl;
        else {
            origin = texture;
            return true;
        }
    }
    return false;
}

void Text::destroyText() {
    SDL_DestroyTexture(origin);
    free(this);
}

Text* createText(std::string str, SDL_Color color){
    Text *self = new Text();
    self->initText(str, color);
    return self;
}


void Effect::initEffect(int duration, int length, SDL_BlendMode mode) {
    keys = new SDL_Color[length];
    this->duration = duration;
    this->length = length;
    this->currentFrame = 0;
    this->mode = mode;
}

void Effect::destroyEffect() {
    free(keys);
    free(this);
}

void copyEffect(const Effect* src, Effect* dest){
    memcpy(dest, src, sizeof(Effect));
    dest->keys = new SDL_Color[src->length];
    memcpy(dest->keys, src->keys, sizeof(SDL_Color) * src->length);
}


void Animation::initAnimation(Texture *origin, const Effect *effect, LoopType lp, int duration, int x, int y,
                              SDL_RendererFlip flip, double angle, At at) {
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


Animation* createAnimation(Texture* origin, const Effect* effect, LoopType lp, int duration, int x, int y, SDL_RendererFlip flip,
                           double angle, At at){
    auto *self = new Animation();
    self->initAnimation(origin, effect, lp, duration, x, y, flip, angle, at);
    return self;
}

void copyAnimation(Animation* src, Animation* dest){
    memcpy(dest, src, sizeof(Animation));
    if (src->effect) {
        dest->effect = new Effect();
        copyEffect(src->effect, dest->effect);
    }
}


void Animation::destroyAnimation() {
    this->effect->destroyEffect();
    free(this);
}

void Score::calcScore() {
    if (got) {
        rank = 0;
        return;
    }
    int gameLevel;
    rank = (double )damage / got + (double )stand / got + got * 50 + killed * 100;
    rank *= gameLevel + 1;
}

void Score::destroyScore() {
    free(this);
}

Score* createScore(){
    auto *score = new Score();
    memset(score, 0, sizeof(Score));
    return score;
}
void addScore(Score* a, Score* b){
    a->got += b->got;
    a->damage += b->damage;
    a->killed += b->killed;
    a->stand += b->stand;
    a->calcScore();
}

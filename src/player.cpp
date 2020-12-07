//
// Created by hyong on 2020/12/7.
//

#include "player.h"
#include <cstdlib>
#include <cstring>

Snake* createSnake(int step, int team, PlayerType playerType){
    auto *self = new Snake();
    self->initSnake(step, team, playerType);
    return self;
}

void Snake::initSnake(int step, int team, PlayerType playerType) {
    this->moveStep = step;
    this->team = team;
    this->num = 0;
    memset(this->buffs, 0, sizeof(this->buffs));
    this->sprites = createLinkList();
    this->score = createScore();
    this->playerType = playerType;
}

void Snake::destroySnake() {
    free(this);
}

//
// Created by hyong on 2020/12/7.
//

#ifndef SDL2GAME_MAP_H
#define SDL2GAME_MAP_H

#include "types.h"

#define SNAKE_MAP_H
#define MAP_SIZE 100

#define MAP_BLOOD_SPILL_RANGE 20
#define MAP_SKULL_SPILL_RANGE 6

void initBlankMap(int w, int h);
void initRandomMap(double floorPercent, int smoothTimes, double trapRate);
void pushMapToRender();

#endif //SDL2GAME_MAP_H

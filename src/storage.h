//
// Created by hyong on 2020/12/7.
//

#ifndef SDL2GAME_STORAGE_H
#define SDL2GAME_STORAGE_H
#include <cstdio>

#include "types.h"

#define STORAGE_PATH "storage.dat"
#define STORAGE_RANKLIST_NUM 10

void updateLocalRanklist(Score*);
Score** insertScoreToRanklist(Score*, int*, Score**);
void destroyRanklist(int n, Score** scores);
void writeRanklist(const char*, int, Score**);
Score** readRanklist(const char* path, int* n);
#endif //SDL2GAME_STORAGE_H

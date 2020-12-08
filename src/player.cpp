#include "player.h"

#include <stdlib.h>
#include <string.h>

void initSnake(Snake* snake, int step, int team, PlayerType playerType) {
    snake->moveStep = step;
    snake->team = team;
    snake->num = 0;
    memset(snake->buffs, 0, sizeof(snake->buffs));
    snake->sprites = createLinkList();
    snake->score = createScore();
    snake->playerType = playerType;
}

/**
 * 创建一个贪吃蛇队伍
 * @param step
 * @param team
 * @param playerType 玩家类型
 * @return 返回一只贪吃蛇队伍
 */
Snake* createSnake(int step, int team, PlayerType playerType) {
    auto* self = static_cast<Snake *>(malloc(sizeof(Snake)));
    initSnake(self, step, team, playerType);
    return self;
}

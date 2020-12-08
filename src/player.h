#ifndef SNAKE__PLAYER_H_
#define SNAKE__PLAYER_H_
#include "types.h"
#include "adt.h"

/**
 * 枚举类型 玩家类型
 * 本地玩家，远程玩家，电脑玩家
 */
typedef enum {
    LOCAL, REMOTE, COMPUTER
} PlayerType;

/**
 * 贪吃蛇的抽象数据结构
 */
class Snake{
public:
    LinkList* sprites;    // 双向链表
    int moveStep;         // 步长
    int team;             //
    int num;              //
    int buffs[BUFF_END];  // 特殊buff
    Score* score;         // 记录分数
    PlayerType playerType;// 玩家类型

    void destroySnake();
} ;

Snake* createSnake(int step, int team, PlayerType playerType);
#endif

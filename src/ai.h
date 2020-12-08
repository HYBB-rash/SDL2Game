#ifndef SNAKE_AI_H_
#define SNAKE_AI_H_

#include "game.h"
#include "player.h"

#define AI_PATH_RANDOM 0.01
#define AI_PREDICT_STEPS 38
#define AI_DECIDE_RATE 4
class Choice{
public:
    int value;
    Direction direction;
} ;

void AiInput(Snake* snake);
int getPowerfulPlayer();
#endif

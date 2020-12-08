//
// Created by hyong on 2020/12/7.
//

#ifndef SDL2GAME_AUDIO_H
#define SDL2GAME_AUDIO_H
#include <SDL.h>
#include <SDL_mixer.h>

#define BGM_FADE_DURATION 800

void playBgm(int);
void playAudio(int);
void randomBgm();
void stopBgm();
void pauseSound();
void resumeSound();
#endif //SDL2GAME_AUDIO_H

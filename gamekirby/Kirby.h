#pragma once
#ifndef __KIRBY__
#define __KIRBY__

#include "CommonFunc.h"
#include "FPS.h"
#include "SDL_InitWindow.h"

const int JUMP = 1;
const int FAIL = 2;
const int RUN = 0;

class Kirby {
protected:
    const int Kirby_FPS = 15;
    const int KIRBY_SPRITES = 6;
    const int SCORE_PER_SECOND = 1;

    int idFrame = 0;
    class FPS kirbyFPS;
    double vJump = 0;
    SDL_Texture* object;
    SDL_Rect gRect, hRect;
    SDL_Rect frameClip[RUNNING_FRAMES];

private:
    int score = 0;
public:
    Kirby();
    ~Kirby() {};
    bool onGround();
    bool inputAction(SDL_Event& e, Mix_Chunk* gJumpMusic);
    void move();

    bool loadImage(SDL_Renderer* renderer);

    void render(SDL_Renderer* renderer, bool run);
    int getPosX() {
        return hRect.x;
    }
    int getPosY() {
        return hRect.y;
    }
    int getRectWidth() {
        return hRect.w;
    }
    int getRectHeight() {
        return hRect.h;
    }
    void cleanUp();
};

#endif /* __KIRBY__ */


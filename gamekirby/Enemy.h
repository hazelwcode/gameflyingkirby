#pragma once
#ifndef __ENEMY__
#define __ENEMY__
#include "CommonFunc.h"
#include "SDL_InitWindow.h"
#include "Object.h"
#include "FPS.h"
#define ii pair<int, int>
static const int TOTAL_FRAMES_OF_ENEMY = 5;
static const int IN_AIR_ENEMY = 1;
static const int ON_GROUND_ENEMY = 2;
static const int ENEMY_RANGE = 200; /*240*/
static const int GOOD_RANGE = 350;
static const int ENEMY_FPS = 15;

const int MIN_HEIGHT = 360;
const int MAX_HEIGHT = 330;

static const double ENEMY_GROUND_WIDTH = 37;
static const string ground_path = { "Resource/Enemy/Cactus.png" };

static ii enemy_pos[5];
static int cnt_num = 0;
class Enemy : BaseObject {
protected:
    int eType, xBack, idFrame = 0, idEnemy;
    SDL_Rect frameClip[TOTAL_FRAMES_OF_ENEMY];
    BaseObject inAirEnemy, onGroundEnemy;
    class FPS eTimer;
public:
    Enemy(int type);

    ~Enemy() {};
    void rebuild();
    bool loadImage(SDL_Renderer* renderer);

    void move(int speed);

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

    int getType() {
        return eType;
    }

    void cleanUp();
};

#endif /* __ENEMY__ */


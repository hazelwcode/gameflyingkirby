#include "Enemy.h"

Enemy::Enemy(int type) {
    eType = type;
    idEnemy = cnt_num;
    hRect.x = SCREEN_WIDTH;

    if (type == IN_AIR_ENEMY) {
        idFrame = 0;
        hRect.y = rand() % (MAX_HEIGHT - MIN_HEIGHT + 1) + MIN_HEIGHT;
    }
    else if (type == ON_GROUND_ENEMY) {
        hRect.y = GROUND;
    }

    if (idEnemy != 0)
        hRect.x = enemy_pos[idEnemy - 1].second + ENEMY_RANGE;

    enemy_pos[idEnemy] = ii(type, hRect.x);
    cnt_num++;
}

void Enemy::rebuild() {
    if (cnt_num >= 3) cnt_num = 0;
    idEnemy = cnt_num;
    hRect.x = SCREEN_WIDTH;

    if (eType == IN_AIR_ENEMY) {
        idFrame = 0;
        hRect.y = rand() % (MAX_HEIGHT - MIN_HEIGHT + 1) + MIN_HEIGHT;
    }
    else if (eType == ON_GROUND_ENEMY) {
        hRect.y = GROUND;
    }

    if (idEnemy != 0)
        hRect.x = enemy_pos[idEnemy - 1].second + ENEMY_RANGE;

    enemy_pos[idEnemy] = ii(eType, hRect.x);
    cnt_num++;
}

bool Enemy::loadImage(SDL_Renderer* renderer) {
    bool success = false;
    if (eType == IN_AIR_ENEMY) {
        eTimer.start();
        BaseObject::loadImage("Resource/Enemy/Bat.png", renderer);
        success = inAirEnemy.loadImage("Resource/Enemy/Bat.png", renderer);
        hRect = { hRect.x, hRect.y, inAirEnemy.getRectWidth() / TOTAL_FRAMES_OF_ENEMY, inAirEnemy.getRectHeight() };
        for (int i = 0; i < TOTAL_FRAMES_OF_ENEMY; i++) {
            frameClip[i].x = hRect.w * i;
            frameClip[i].y = 0;
            frameClip[i].w = hRect.w;
            frameClip[i].h = hRect.w;
        }
    }
    else if (eType == ON_GROUND_ENEMY) {
        string path = ground_path;
        BaseObject::loadImage(path, renderer);
        success = onGroundEnemy.loadImage(path, renderer);
        hRect = { hRect.x, hRect.y, onGroundEnemy.getRectWidth(), onGroundEnemy.getRectHeight() };

    }
    return success;
}

void Enemy::move(int speed) {
    int max_pos = 0;
    hRect.x = enemy_pos[idEnemy].second;
    hRect.x = hRect.x - (ENEMY_SPEED + speed);
    enemy_pos[idEnemy] = ii(eType, hRect.x);
    if (hRect.x + hRect.w <= 0) {
        for (int i = 0; i < 3; i++) {
            ii s = enemy_pos[i];
            if (i == idEnemy) continue;
            max_pos = max(s.second, max_pos);
        }
        hRect.x = rand() % ENEMY_RANGE + max(SCREEN_WIDTH + rand() % GOOD_RANGE, max_pos + ENEMY_RANGE);
        enemy_pos[idEnemy] = ii(eType, hRect.x);
        for (int i = 0; i < 3; i++) {
            if (i == idEnemy) continue;
            if (enemy_pos[i].second > SCREEN_WIDTH) {
                swap(enemy_pos[i].second, enemy_pos[idEnemy].second);

                break;
            }
        }
        if (eType == IN_AIR_ENEMY) {
            idFrame = 0;
            hRect.y = rand() % (MAX_HEIGHT - MIN_HEIGHT + 1) + MIN_HEIGHT;
        }

        else if (eType == ON_GROUND_ENEMY) {
            hRect.y = GROUND;
        }
    }
}

void Enemy::render(SDL_Renderer* renderer, bool run) {
    if (eType == IN_AIR_ENEMY) {
        SDL_RenderCopy(renderer, object, &frameClip[idFrame], &hRect);
        int real_enemy_time = eTimer.getTicks();
        if (real_enemy_time >= 1000 / ENEMY_FPS && run == true) {
            idFrame++;
            if (idFrame == TOTAL_FRAMES_OF_ENEMY) idFrame = 0;
            eTimer.start();
        }
    }
    else if (eType == ON_GROUND_ENEMY) {
        SDL_RenderCopy(renderer, object, &gRect, &hRect);
    }
}

void Enemy::cleanUp() {
    cnt_num = 0;
    BaseObject::cleanUp();
    inAirEnemy.cleanUp();
    onGroundEnemy.cleanUp();
}

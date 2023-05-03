#pragma once

#ifndef __BUTTON__
#define __BUTTON__

#include "CommonFunc.h"
#include "FPS.h"
#include "SDL_InitWindow.h"


class Button {
#define FRAMES_BUTTON 2
protected:
    int idFrame = 0;
    SDL_Texture* object;
    SDL_Rect gRect, hRect;
    SDL_Rect frameClip[FRAMES_BUTTON];
private:
    int score = 0;
public:
    Button();
    ~Button() {};
    bool loadImage(string path, SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer);

    SDL_Texture* getObject() const {
        return object;
    }
    SDL_Rect getRect() const {
        return hRect;
    }

    int getPosX() {
        return hRect.x;
    }
    void setPosX(int posX) { this->hRect.x = posX; }
    void setPosY(int posY) { this->hRect.y = posY; }
    int getPosY() {
        return hRect.y;
    }
    int getRectWidth() {
        return hRect.w;
    }
    int getRectHeight() {
        return hRect.h;
    }

    void setIdFrame(int idFrame) { this->idFrame = idFrame; };
    int getIdFrame() { return this->idFrame; };
    void sethRectWidth(int width) {
        this->hRect.w = width;
    }
    void sethRectHeight(int height) {
        this->hRect.h = height;
    }
    void cleanUp();
};

#endif /* __BUTTON__ */


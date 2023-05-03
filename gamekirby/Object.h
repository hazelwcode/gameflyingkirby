#pragma once
#ifndef __OBJECT__
#define __OBJECT__
#include "CommonFunc.h"

class BaseObject {
protected:
    SDL_Texture* object;
    SDL_Rect gRect, hRect;

public:
    BaseObject();
    ~BaseObject();
    void setRect(const int& x, const int& y) {
        gRect.x = x;
        gRect.y = y;
    }
    void setDesRect(const int& x, const int& y, const int& w, const int& h) {
        hRect.x = x;
        hRect.y = y;
        hRect.w = w;
        hRect.h = h;
        if (w < 0 && h < 0) {
            hRect.w = gRect.w;
            hRect.h = gRect.h;
        }
    }
    SDL_Texture* getObject() const {
        return object;
    }
    SDL_Rect getRect() const {
        return gRect;
    }
    int getRectWidth() {
        return hRect.w;
    }
    int getRectHeight() {
        return hRect.h;
    }

    bool loadImage(string path, SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer);

    void render(int x, int y, SDL_Renderer* renderer);

    void cleanUp();
};

#endif /* __OBJECT__ */

#ifndef Map_h
#define Map_h

#include "CommonFunc.h"
#include "Object.h"

class Map {
private:
    string addressBackGround;
    string addressBgGround;

    BaseObject backGround;
    BaseObject Ground;

public:
    Map() {
        addressBgGround = "Resource/BackGround/ground.png";
        addressBackGround = "Resource/BackGround/Background.png";
    };
    ~Map() {};

    bool loadBackGround(SDL_Renderer* renderer);
    bool loadGround(SDL_Renderer* renderer);

    void renderScrollingBackground(/*vector <double> &offSetSpeed,*/ SDL_Renderer* renderer);
    void renderScrollingGround(int& pos, SDL_Renderer* renderer);

    void cleanUp();
};

#endif /* Map_h */

#pragma once

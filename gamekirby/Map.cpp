#include "Map.h"
#include "CommonFunc.h"


bool Map::loadBackGround(SDL_Renderer* renderer) {
    bool success = true;

    success = backGround.loadImage(addressBackGround.c_str(), renderer);
    return success;
}

bool Map::loadGround(SDL_Renderer* renderer) {
    return Ground.loadImage(addressBgGround, renderer);
}

void Map::renderScrollingBackground(SDL_Renderer* renderer) {
    backGround.render(renderer);
}

void Map::renderScrollingGround(int& pos, SDL_Renderer* renderer) {
    pos = pos - (GROUND_SPEED);
    if (pos < -SCREEN_WIDTH) pos = 0;
    Ground.render(pos, 0, renderer);
    Ground.render(SCREEN_WIDTH + pos, 0, renderer);
}

void Map::cleanUp() {
    Ground.cleanUp();
    backGround.cleanUp();
}


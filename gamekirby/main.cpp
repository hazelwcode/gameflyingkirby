#include "CommonFunc.h"
#include "FPS.h"
#include "SDL_InitWindow.h"
#include "Object.h"
#include "Map.h"
#include "Kirby.h"
#include "Enemy.h"
#include "FlyingKirby.h"

int main(int argc, char* argv[]) {
    srand((unsigned int)time(0));


    FlyingKirby* dinoGame = new FlyingKirby;
    dinoGame->menuGame();

    return 0;
}

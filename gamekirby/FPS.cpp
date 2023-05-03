#include "CommonFunc.h"
#include "FPS.h"

FPS::FPS() {
    startTick = 0;
    pausedTick = 0;
    paused = started = false;
}

void FPS::start() {
    started = true;
    paused = false;
    startTick = SDL_GetTicks();
}

void FPS::stop() {
    paused = true;
    started = false;
}

void FPS::pause() {
    if (started == true && paused == false) {
        paused = true;
        pausedTick = SDL_GetTicks() - startTick;
    }
}

void FPS::unpause() {
    if (paused == true) {
        paused = false;
        startTick = SDL_GetTicks();
        pausedTick = 0;
    }
}

int FPS::getTicks() {
    if (started == true) {
        if (paused == true) {
            return pausedTick;
        }
        else {
            return SDL_GetTicks() - startTick;
        }
    }
    return 0;
}

bool FPS::isStarted() {
    return started;
}

bool FPS::isPaused() {
    return paused;
}


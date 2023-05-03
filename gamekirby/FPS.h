#pragma once
#ifndef __FPS__
#define __FPS__
class FPS {
private:
    int startTick;
    int pausedTick;

    bool paused;
    bool started;

public:
    FPS();
    ~FPS() {};

    void start();
    void stop();
    void pause();
    void unpause();

    bool isStarted();
    bool isPaused();

    int getTicks();
};

#endif /* __FPS__ */


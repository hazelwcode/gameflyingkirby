#pragma once
#ifndef SDL_InitWindow_h
#define SDL_InitWindow_h

#include <iostream>
#include <SDL.h>

using namespace std;

void logSDLError(const std::string& msg, bool fatal = false);
void initSDL(SDL_Window*& window, SDL_Renderer*& renderer, string WINDOW_TITLE, int SCREEN_WIDTH, int SCREEN_HEIGHT);
void quitSDL(SDL_Window*& window, SDL_Renderer*& renderer);
void waitUntilKeyPressed();

#endif /* SDL_InitWindow.h */

#include "Button.h"

Button::Button() {
    hRect.w = 150;
    hRect.h = 98;
}

bool Button::loadImage(string path, SDL_Renderer* renderer) {
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadSurface = IMG_Load(path.c_str());

    if (loadSurface != NULL) {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadSurface);
        if (newTexture != NULL) {
            gRect.w = loadSurface->w;
            gRect.h = loadSurface->h;
            object = newTexture;

            for (int i = 0; i < FRAMES_BUTTON; i++) {
                frameClip[i].x = hRect.w * i;
                frameClip[i].y = 0;
                frameClip[i].w = hRect.w;
                frameClip[i].h = hRect.h;
            }

            SDL_FreeSurface(loadSurface);
            return true;
        }
        else  logSDLError("Unable to create texture from " + path + " SDL_Error: ", SDL_GetError());
    }
    else logSDLError("Unable to load image " + path + " SDL_image Error: ", IMG_GetError());

    return false;
}

void Button::render(SDL_Renderer* renderer) {
    hRect.w = frameClip[idFrame].w;
    hRect.h = frameClip[idFrame].h;
    SDL_RenderCopy(renderer, object, &frameClip[idFrame], &hRect);
}

void Button::cleanUp() {
    SDL_DestroyTexture(object);
}

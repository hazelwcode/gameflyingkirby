#include "SDL_InitWindow.h"
#include "Object.h"

BaseObject::BaseObject() {
    object = NULL;
    gRect.x = 0;
    gRect.y = 0;
    gRect.w = 0;
    gRect.h = 0;
}

BaseObject::~BaseObject() {

}

bool BaseObject::loadImage(string path, SDL_Renderer* renderer) {
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadSurface = IMG_Load(path.c_str());

    if (loadSurface != NULL) {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadSurface);
        if (newTexture != NULL) {
            gRect.w = hRect.w = loadSurface->w;
            gRect.h = hRect.h = loadSurface->h;
            object = newTexture;
            SDL_FreeSurface(loadSurface);
            return true;
        }
        else  logSDLError("Unable to create texture from " + path + " SDL_Error: ", SDL_GetError());
    }
    else logSDLError("Unable to load image " + path + " SDL_image Error: ", IMG_GetError());

    return false;
}

void BaseObject::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, object, &gRect, &hRect);
}
void BaseObject::render(int x, int y, SDL_Renderer* renderer) {
    SDL_Rect dest_rect = { x, y, hRect.w, hRect.h };
    SDL_RenderCopy(renderer, object, &gRect, &dest_rect);
}
void BaseObject::cleanUp() {
    if (object != NULL) {
        SDL_DestroyTexture(object);
        object = NULL;
        gRect.w = 0;
        gRect.h = 0;
        hRect.w = 0;
        hRect.h = 0;
    }
}


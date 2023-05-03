#include "Kirby.h"

Kirby::Kirby() {
    hRect.x = SCREEN_WIDTH - 700;
    hRect.y = GROUND;
    hRect.w = hRect.h = 57;

}

bool Kirby::onGround() {
    return hRect.y == GROUND;
}

bool Kirby::inputAction(SDL_Event& e, Mix_Chunk* gJumpMusic) {
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
        case SDLK_SPACE:
        case SDLK_UP: {
            if (onGround() == true) {
                vJump = 8;
                return true;
            }
        }
        }
    }
    return false;
}

void Kirby::move() {
    vJump -= GRAVITY_FALL;
    hRect.y += -vJump;
    if (hRect.y >= GROUND) vJump = 0;
    hRect.y = min(GROUND, hRect.y);
    score += SCORE_PER_SECOND;
}

bool Kirby::loadImage(SDL_Renderer* renderer) {
    kirbyFPS.start();
    string path = "Resource/Kirby/FlyingKirby.png";
    ;
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadSurface = IMG_Load(path.c_str());

    if (loadSurface != NULL) {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadSurface);
        if (newTexture != NULL) {
            gRect.w = loadSurface->w;
            gRect.h = loadSurface->h;
            object = newTexture;

            for (int i = 0; i < KIRBY_SPRITES; i++) {
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

void Kirby::render(SDL_Renderer* renderer, bool run) {
    hRect.w = frameClip[idFrame].w;
    hRect.h = frameClip[idFrame].h;

    SDL_RenderCopy(renderer, object, &frameClip[idFrame], &hRect);

    int real_kirby_time = kirbyFPS.getTicks();
    if (real_kirby_time >= 1000 / Kirby_FPS && run == true) {
        idFrame++;
        if (idFrame == 6) idFrame = 0;
        kirbyFPS.start();
    }
}

void Kirby::cleanUp() {
    SDL_DestroyTexture(object);
}

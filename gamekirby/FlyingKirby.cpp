#include "FlyingKirby.h"
#include "Button.h"
#include "CommonFunc.h"
#include "Mouse.h"
#include "LTexture.h"

Mix_Music* gBackgroundMusic = NULL;
Mix_Music* gMenuMusic = NULL;
Mix_Chunk* gClickMusic = NULL;
Mix_Chunk* gJumpMusic = NULL;
Mix_Chunk* gLoseMusic = NULL;

class Map Map_data;
class Kirby kirby;
class Enemy Air(IN_AIR_ENEMY), Ground1(ON_GROUND_ENEMY), Ground2(ON_GROUND_ENEMY);
FPS timer;

bool loadBackGround() {
    gJumpMusic = Mix_LoadWAV("Resource/Sound/jump_sound.wav");
    gLoseMusic = Mix_LoadWAV("Resource/Sound/lose_sound.wav");
    gBackgroundMusic = Mix_LoadMUS("Resource/Sound/background_sound.wav");
    if (gBackgroundMusic == NULL) cout << Mix_GetError();
    return (Map_data.loadGround(gRenderer)
        && Map_data.loadBackGround(gRenderer)
        );
}

bool checkColi(Kirby kirby, Enemy enemy) {
    SDL_Rect d_rect = { kirby.getPosX() + 10, kirby.getPosY() + 10, kirby.getRectWidth() - 25, kirby.getRectHeight() - 20 };
    SDL_Rect e_rect;
    if (enemy.getType() == ON_GROUND_ENEMY) {
        e_rect = { enemy.getPosX() + 15, enemy.getPosY() + 15, enemy.getRectWidth() - 30, enemy.getRectHeight() - 0 };
    }
    else {
        e_rect = { enemy.getPosX() + 15, enemy.getPosY() + 4, enemy.getRectWidth() - 15, enemy.getRectHeight() - 15 };
    }
    return SDL_HasIntersection(&d_rect, &e_rect);
}

void process(int speed) {
    kirby.move();
    Air.move(speed);
    Ground1.move(speed);
    Ground2.move(speed);
    kirby.render(gRenderer, true);
    Air.render(gRenderer, true);
    Ground1.render(gRenderer, true);
    Ground2.render(gRenderer, true);
}

void FlyingKirby::menuGame() {
    initSDL(gWindow, gRenderer, WINDOW_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);
    BaseObject backgroundMenu;
    backgroundMenu.loadImage("Resource/Background/menu.png", gRenderer);

    Button playButton;
    playButton.loadImage("Resource/Button/play_button.png", gRenderer);
    playButton.setIdFrame(0);
    playButton.setPosX(PLAY_BUTTON_POSX);
    playButton.setPosY(PLAY_BUTTON_POSY);

    Button helpButton;
    helpButton.loadImage("Resource/Button/help_button.png", gRenderer);
    helpButton.setIdFrame(0);
    helpButton.setPosX(HELP_BUTTON_POSX);
    helpButton.setPosY(HELP_BUTTON_POSY);

    Button exitButton;
    exitButton.loadImage("Resource/Button/exit_button.png", gRenderer);
    exitButton.setIdFrame(0);
    exitButton.setPosX(EXIT_BUTTON_POSX);
    exitButton.setPosY(EXIT_BUTTON_POSY);

    FPS fpsTimer;
    bool quit = false;
    Mouse mouse;
    while (!quit) {
        fpsTimer.start();
        mouse.mouseHandleEvent();
        bool selectPlayButton = bool(mouse.checkMouseInButton(&playButton));
        bool selectHelpButton = bool(mouse.checkMouseInButton(&helpButton));
        bool selectExitButton = bool(mouse.checkMouseInButton(&exitButton));
        playButton.setIdFrame(selectPlayButton);
        helpButton.setIdFrame(selectHelpButton);
        exitButton.setIdFrame(selectExitButton);
        while (SDL_PollEvent(&gEvent)) {
            if (gEvent.type == SDL_QUIT) {
                quit = true;
                exit(0);
            }
            if (gEvent.type == SDL_MOUSEBUTTONDOWN) {
                if (selectPlayButton) {
                    display = typeDisplay::PLAY;
                }
                if (selectHelpButton) {
                    display = typeDisplay::HELP;
                }
                if (selectExitButton) {
                    display = typeDisplay::EXIT;
                }
            }
        }
        SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR,
            RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(gRenderer);
        backgroundMenu.render(gRenderer);
        playButton.render(gRenderer);
        helpButton.render(gRenderer);
        exitButton.render(gRenderer);

        //if (display != typeDisplay::MENU) {
        //    mouse.cleanUp();
        //    playButton.cleanUp();
        //}

        switch (display) {
        case typeDisplay::PLAY:
            displayGame();
            break;
        case typeDisplay::HELP:
            displayHelpGame();
            break;
        case typeDisplay::EXIT:
            return;
            break;
        }
        SDL_RenderPresent(gRenderer);

        int realTime = fpsTimer.getTicks();
        int timeOneFrame = 1000 / FRAME_PER_SECOND;
        if (realTime < timeOneFrame) {
            int delayTime = timeOneFrame - realTime;
            if (delayTime >= 0)
                SDL_Delay(delayTime);
        }
    }

}

TTF_Font* fontGame;

void FlyingKirby::displayGame() {
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_PlayMusic(gBackgroundMusic, -1);
    if (loadBackGround() == false) {
        cout << "Can't not load Background!!!";
        return;
    }
    if (TTF_Init() == -1) {
        cout << "Can't not load TTF!!!";
        return;
    }
    fontGame = TTF_OpenFont("Resource/Font/arcade_gamer.ttf", FONT_SIZE);
    if (fontGame == NULL) {
        cout << "Can't not load Font!!!";
        return;
    }

    const int STATUS_GAME_BUTTON_X = 25;
    const int STATUS_GAME_BUTTON_Y = 25;
    const int SET_CLIP_STATUS_GAMEBUTTON_X = 34;
    const int SET_CLIP_STATUS_GAMEBUTTON_Y = 22;

    Button pauseButton;
    pauseButton.setIdFrame(0);
    pauseButton.setPosX(STATUS_GAME_BUTTON_X);
    pauseButton.setPosY(STATUS_GAME_BUTTON_Y);
    pauseButton.sethRectHeight(SET_CLIP_STATUS_GAMEBUTTON_X);
    pauseButton.sethRectWidth(SET_CLIP_STATUS_GAMEBUTTON_Y);
    pauseButton.loadImage("Resource/Button/pause_button.png", gRenderer);

    Button pauseButtonRemove;
    pauseButtonRemove.setIdFrame(0);
    pauseButtonRemove.setPosX(STATUS_GAME_BUTTON_X);
    pauseButtonRemove.setPosY(STATUS_GAME_BUTTON_Y);
    pauseButtonRemove.sethRectHeight(SET_CLIP_STATUS_GAMEBUTTON_X);
    pauseButtonRemove.sethRectWidth(SET_CLIP_STATUS_GAMEBUTTON_Y);
    pauseButtonRemove.loadImage("Resource/Button/pause_button_remove.png", gRenderer);

    Button continueButton;
    continueButton.setIdFrame(0);
    continueButton.setPosX(STATUS_GAME_BUTTON_X);
    continueButton.setPosY(STATUS_GAME_BUTTON_Y);
    continueButton.sethRectHeight(SET_CLIP_STATUS_GAMEBUTTON_X);
    continueButton.sethRectWidth(SET_CLIP_STATUS_GAMEBUTTON_Y);
    continueButton.loadImage("Resource/Button/continue_button.png", gRenderer);

    const int SOUND_BUTTON_X = 75;
    const int SOUND_BUTTON_Y = 25;
    const int SET_CLIP_SOUND_BUTTON_X = 34;
    const int SET_CLIP_SOUND_BUTTON_Y = 40;
    Button soundOnButtonRemove;
    soundOnButtonRemove.setIdFrame(0);
    soundOnButtonRemove.setPosX(SOUND_BUTTON_X);
    soundOnButtonRemove.setPosY(SOUND_BUTTON_Y);
    soundOnButtonRemove.sethRectHeight(SET_CLIP_SOUND_BUTTON_X);
    soundOnButtonRemove.sethRectWidth(SET_CLIP_SOUND_BUTTON_Y);
    soundOnButtonRemove.loadImage("Resource/Button/soundOn_button_remove.png", gRenderer);

    Button soundOnButton;
    soundOnButton.setIdFrame(0);
    soundOnButton.setPosX(SOUND_BUTTON_X);
    soundOnButton.setPosY(SOUND_BUTTON_Y);
    soundOnButton.sethRectHeight(SET_CLIP_SOUND_BUTTON_X);
    soundOnButton.sethRectWidth(SET_CLIP_SOUND_BUTTON_Y);
    soundOnButton.loadImage("Resource/Button/soundOn_button.png", gRenderer);

    Button soundOffButton;
    soundOffButton.setIdFrame(0);
    soundOffButton.setPosX(SOUND_BUTTON_X);
    soundOffButton.setPosY(SOUND_BUTTON_Y);
    soundOffButton.sethRectHeight(SET_CLIP_SOUND_BUTTON_X);
    soundOffButton.sethRectWidth(SET_CLIP_SOUND_BUTTON_Y);
    soundOffButton.loadImage("Resource/Button/soundOff_button.png", gRenderer);

    SDL_Event event;
    LTexture scoreText;
    LTexture highScoreText;
    Mouse mouse;
    bool quit = false;
    while (!quit) {
        Mix_PlayMusic(gBackgroundMusic, -1);
        Air.loadImage(gRenderer);
        Ground1.loadImage(gRenderer);
        Ground2.loadImage(gRenderer);
        kirby.loadImage(gRenderer);

        bool isRunning = true;
        int groundPos = GROUND_SPEED;

        Air.rebuild();
        Ground1.rebuild();
        Ground2.rebuild();
        int curTime = 0, score = 0, speed = 0;
        ifstream file("Resource/Database/HighScore.txt");
        int highScore;
        file >> highScore;
        file.close();
        bool diedKirby = false;
        int curButton = typeButton::PAUSE;
        int isPauseGame = false;
        sound = true;
        while (isRunning) {
            score = curTime / (FRAME_PER_SECOND / 2);
            bool selectPauseButton = false, selectContinueButton = false;
            bool selectOnButton = false, selectOffButton = false;
            SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            SDL_RenderClear(gRenderer);
            while (SDL_PollEvent(&event)) {
                mouse.mouseHandleEvent();

                selectPauseButton = bool(mouse.checkMouseInButton(&pauseButton));
                pauseButton.setIdFrame(selectPauseButton);

                selectContinueButton = bool(mouse.checkMouseInButton(&continueButton));
                continueButton.setIdFrame(selectContinueButton);

                selectOnButton = bool(mouse.checkMouseInButton(&soundOnButton));
                soundOnButton.setIdFrame(selectOnButton);

                selectOffButton = bool(mouse.checkMouseInButton(&soundOffButton));
                soundOffButton.setIdFrame(selectOffButton);

                if (event.type == SDL_QUIT) {
                    isRunning = false;
                    quit = true;
                }
                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    if (curButton == typeButton::PAUSE) {
                        if (selectPauseButton) {
                            isPauseGame = true;
                            Mix_HaltMusic();
                            curButton = typeButton::CONTINUE;
                        }
                    }
                    else {
                        if (selectContinueButton) {
                            isPauseGame = false;
                            if (sound == true) Mix_PlayMusic(gBackgroundMusic, -1);
                            curButton = typeButton::PAUSE;
                        }
                    }
                    if (selectOnButton) {
                        if (sound == true) {
                            sound = false;
                            Mix_HaltMusic();
                        }
                        else {
                            Mix_PlayMusic(gBackgroundMusic, -1);
                            sound = true;
                        }
                    }

                }
                if (isPauseGame == false) {
                    if (kirby.inputAction(event, gJumpMusic)) {
                        if (sound == true) Mix_PlayChannel(-1, gJumpMusic, 0);
                    }
                }
            }
            if (isPauseGame == true) {
                Map_data.renderScrollingBackground(gRenderer);
                kirby.render(gRenderer, false);
                Air.render(gRenderer, false);
                Ground1.render(gRenderer, false);
                Ground2.render(gRenderer, false);
            }
            if (diedKirby == false && isPauseGame == false) {
                timer.start();
                ++curTime;
                Map_data.renderScrollingBackground(gRenderer);
                Map_data.renderScrollingGround(groundPos, gRenderer);
                const int MAX_SPEED = 2;
                const int TIME_CHANGE_SPEED = 10;
                speed = min(MAX_SPEED, curTime / (FRAME_PER_SECOND * TIME_CHANGE_SPEED));
                process(speed);
            }
            if (diedKirby == true) continue;
            const int RIGHT_MARGIN = 75;
            const int TOP_MARGIN = 10;
            scoreText.setColor(LTexture::WHITE_COLOR);
            string scoreStr = "SCORE: " + to_string(score);
            scoreText.setText(scoreStr);
            scoreText.loadFromRenderText(fontGame, gRenderer);

            const int DISTANCE_TEXT = 40;
            highScore = max(highScore, score);
            highScoreText.setColor(LTexture::WHITE_COLOR);
            string highScoreStr = "HIGHSCORE: " + to_string(highScore);
            highScoreText.setText(highScoreStr);
            highScoreText.loadFromRenderText(fontGame, gRenderer);

            const int SCORE_TEXT_POS_X = 700;
            const int HIGHSCORE_TEXT_POS_X = 638;

            scoreText.showText(gRenderer, SCORE_TEXT_POS_X, TOP_MARGIN);
            highScoreText.showText(gRenderer, HIGHSCORE_TEXT_POS_X, TOP_MARGIN + DISTANCE_TEXT);

            if (score >= highScore) {
                ofstream file("Resource/Database/HighScore.txt");
                file << highScore;
                file.close();
            }

            if (curButton == typeButton::PAUSE)
                pauseButton.render(gRenderer);
            else
                continueButton.render(gRenderer);
            if (sound == true)
                soundOnButton.render(gRenderer);
            else
                soundOffButton.render(gRenderer);


            SDL_RenderPresent(gRenderer);
            if (checkColi(kirby, Air) || checkColi(kirby, Ground1) || checkColi(kirby, Ground2)) {
                if (diedKirby == false) {
                    if (sound == true) {
                        Mix_PlayChannel(-1, gLoseMusic, 0);
                        Mix_PauseMusic();
                    }
                }

                diedKirby = true;

                pauseButtonRemove.render(gRenderer);
                soundOnButtonRemove.render(gRenderer);

                SDL_Surface* loadSurface = IMG_Load("Resource/lose.png");
                SDL_Texture* lose_texture = SDL_CreateTextureFromSurface(gRenderer, loadSurface);
                SDL_FreeSurface(loadSurface);
                SDL_RenderCopy(gRenderer, lose_texture, NULL, NULL);
                SDL_RenderPresent(gRenderer);
                SDL_DestroyTexture(lose_texture);

                while (diedKirby) {
                    while (SDL_WaitEvent(&event)) {
                        if (event.type == SDL_QUIT) {
                            isRunning = false;
                            quit = true;
                            diedKirby = false;
                            break;
                        }
                        else if (event.type == SDL_KEYDOWN) {
                            switch (event.key.keysym.sym) {
                            case SDLK_SPACE:
                                isRunning = false;
                                break;

                            case SDLK_ESCAPE:
                                isRunning = false;
                                quit = true;
                                diedKirby = false;
                                break;
                            }
                        }
                        if (isRunning == false) {
                            diedKirby = false;
                            break;
                        }
                    }
                }
            }

            //if (diedKirby == true) continue;
            //const int RIGHT_MARGIN = 75;
            //const int TOP_MARGIN = 10;
            //scoreText.setColor(LTexture::WHITE_COLOR);
            //string scoreStr = "SCORE: " + to_string(score);
            //scoreText.setText(scoreStr);
            //scoreText.loadFromRenderText(fontGame, gRenderer);

            //const int DISTANCE_TEXT = 40;
            //highScore = max(highScore, score);
            //highScoreText.setColor(LTexture::WHITE_COLOR);
            //string highScoreStr = "HIGHSCORE: " + to_string(highScore);
            //highScoreText.setText(highScoreStr);
            //highScoreText.loadFromRenderText(fontGame, gRenderer);

            //const int SCORE_TEXT_POS_X = 700;
            //const int HIGHSCORE_TEXT_POS_X = 638;

            //scoreText.showText(gRenderer, SCORE_TEXT_POS_X, TOP_MARGIN);
            //highScoreText.showText(gRenderer, HIGHSCORE_TEXT_POS_X, TOP_MARGIN + DISTANCE_TEXT);
            //
            //if (score >= highScore) {
            //    ofstream file("Resource/Database/HighScore.txt");
            //    file << highScore;
            //    file.close();
            //}

            //if (curButton == typeButton::PAUSE)
            //    pauseButton.render(gRenderer);
            //else
            //    continueButton.render(gRenderer);
            //if (sound == true)
            //    soundOnButton.render(gRenderer);
            //else
            //    soundOffButton.render(gRenderer);
            //SDL_RenderPresent(gRenderer);

            int realTime = timer.getTicks();
            int timeOneFrame = 1000 / FRAME_PER_SECOND;
            if (realTime < timeOneFrame) {
                int delayTime = timeOneFrame - realTime;
                SDL_Delay(delayTime);
            }
        }
        Air.cleanUp();
        Ground1.cleanUp();
        Ground2.cleanUp();
    }
    Map_data.cleanUp();
    Mix_FreeMusic(gBackgroundMusic);
    gBackgroundMusic = NULL;

    Mix_FreeMusic(gMenuMusic);
    gMenuMusic = NULL;

    Mix_FreeChunk(gClickMusic);
    gClickMusic = NULL;

    Mix_FreeChunk(gJumpMusic);
    gJumpMusic = NULL;

    Mix_FreeChunk(gLoseMusic);
    gLoseMusic = NULL;
    quitSDL(gWindow, gRenderer);
}

void FlyingKirby::displayHelpGame() {
    BaseObject backgroundMenu;
    backgroundMenu.loadImage("Resource/Background/instruction.png", gRenderer);

    const int SET_CLIP_BACKBUTTION_HEIGHT = 78;
    const int SET_CLIP_BACKBUTTION_WIDTH = 100;

    Button backButton;
    backButton.sethRectHeight(SET_CLIP_BACKBUTTION_HEIGHT);
    backButton.sethRectWidth(SET_CLIP_BACKBUTTION_WIDTH);
    backButton.loadImage("Resource/Button/back_button.png", gRenderer);
    backButton.setIdFrame(0);
    backButton.setPosX(BACK_BUTTON_POSX);
    backButton.setPosY(BACK_BUTTON_POSY);

    FPS fpsTimer;
    bool quit = false;
    Mouse mouse;
    while (!quit) {
        fpsTimer.start();
        mouse.mouseHandleEvent();
        bool selectBackButton = bool(mouse.checkMouseInButton(&backButton));
        backButton.setIdFrame(selectBackButton);
        while (SDL_PollEvent(&gEvent)) {
            if (gEvent.type == SDL_QUIT) {
                quit = true;
                exit(0);
            }
            if (gEvent.type == SDL_MOUSEBUTTONDOWN) {
                if (selectBackButton) {
                    display = typeDisplay::RE_MENU;
                    SDL_RenderPresent(gRenderer);
                    quit = true;
                    break;
                }
            }
        }

        SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR,
            RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(gRenderer);

        backgroundMenu.render(gRenderer);
        backButton.render(gRenderer);
        SDL_RenderPresent(gRenderer);

        int realTime = fpsTimer.getTicks();
        int timeOneFrame = 1000 / FRAME_PER_SECOND;
        if (realTime < timeOneFrame) {
            int delayTime = timeOneFrame - realTime;
            if (delayTime >= 0)
                SDL_Delay(delayTime);
        }
    }
    backgroundMenu.cleanUp();
    backButton.cleanUp();
    //startGame();
}

#pragma once
#ifndef  __FLYINGKIRBY__
#define __FLYINGKIRBY__

#include "CommonFunc.h"
#include "FPS.h"
#include "SDL_InitWindow.h"
#include "Object.h"
#include "Map.h"
#include "Kirby.h"
#include "Enemy.h"

class FlyingKirby {
public:
	enum typeDisplay {
		MENU = 0,
		PLAY = 1,
		HELP = 2,
		EXIT = 3,
		BACK = 4,
		RE_MENU = 5,
	};

	enum typeButton {
		PAUSE = 0,
		CONTINUE = 1,
	};
	void menuGame();
	void displayGame();
	void displayHelpGame();
private:
	int display = typeDisplay::MENU;
	bool sound = true;
};
#endif // !__FLYINGKIRBY__


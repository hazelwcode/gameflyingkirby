#pragma once
#ifndef __MOUSE__
#define __MOUSE__

#include "Object.h"
#include "Button.h"

using namespace std;

class Mouse : public BaseObject {
private:
	int mouseX;
	int mouseY;
	void setPosition(int mouseX, int mouseY);
public:
	Mouse() {}
	void mouseHandleEvent();
	bool checkMouseInButton(Button* button);
};

#endif

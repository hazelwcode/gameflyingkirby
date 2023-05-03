#include "Mouse.h"
#include "Button.h"

void Mouse::mouseHandleEvent() {
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	setPosition(mouseX, mouseY);
	gRect.x = mouseX;
	gRect.y = mouseY;
}

void Mouse::setPosition(int mouseX, int mouseY) {
	this->mouseX = mouseX;
	this->mouseY = mouseY;
}

bool Mouse::checkMouseInButton(Button* button) {
	SDL_Rect rect = button->getRect();
	if (mouseX < rect.x
		|| mouseX > rect.x + rect.w - 1
		|| mouseY < rect.y
		|| mouseY > rect.y + rect.h - 1) return false;

	return true;
}


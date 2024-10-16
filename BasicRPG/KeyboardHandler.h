#pragma once

#include <SDL.h>
#include <map>

#include "KeyboardCodes.h"

class KeyboardHandler
{
public:
	void handleKeyboardEvent(SDL_Event event);

	bool isPressed(SDL_Scancode keyCode);

	bool isReleased(SDL_Scancode keyCode);

private:
	std::map<SDL_Scancode, bool> keyCodes;
};


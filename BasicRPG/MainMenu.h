#pragma once
#include <exception>

#include "Menu.h"
#include "NewGameButton.h"
#include "ExitButton.h"
#include "ButtonType.h"
#include "GameEvents.h"

class MainMenu :
    public Menu
{
public:

    MainMenu(SDL_Renderer* renderer, int width, int height, std::string image_path, int sprite_w = 0, int sprite_h = 0);

    GameEvents handelEvent(SDL_Event* e);
};


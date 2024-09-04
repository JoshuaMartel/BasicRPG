#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <memory>
#include <exception>

#include "MainMenu.h"
#include "Constants.h"
#include "GameMap.h"
#include "FileHandler.h"
#include "Player.h"

class Game
{
public:
	Game(int window_width, int window_height);

	~Game();

	bool init();

	void loop();

	void close();

private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	std::unique_ptr<MainMenu> p_main_menu;

	std::unique_ptr<GameMap> p_cur_map;

	std::unique_ptr<Player> p_player;

	int m_window_width;
	int m_window_height;
};


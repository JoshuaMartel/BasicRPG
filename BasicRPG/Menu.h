#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include <memory> 

#include "Texture.h"
#include "Button.h"

class Menu
{
public:
	Menu();

	~Menu();

	Menu(const Menu& m);

	bool init(SDL_Renderer* renderer, int width, int height, std::string image_path, int sprite_w = 0, int sprite_h = 0);

	void render(SDL_Renderer* renderer);

	bool handleEvent(SDL_Event* e);

private:
	int m_window_width;
	int m_window_height;
	int m_num_sprites_width;
	int m_num_sprites_height;

	std::string m_image_path;
	std::vector<std::unique_ptr<Button>> m_buttons;

	TTF_Font* p_font;
	SDL_Color m_text_colour;
};


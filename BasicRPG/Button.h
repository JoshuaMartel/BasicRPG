#pragma once

#include <SDL.h>

#include "Texture.h"

class Button
{
public:
	Button();

	// initislise class and return success or failure to initialise
	bool init(SDL_Renderer* renderer, int x, int y, 
		std::string font_path, std::string text, int font_size, SDL_Color text_color);

	// Sets top left position
	void setPosition(int x, int y);

	// Handles mouse event
	bool handleEvent(SDL_Event* e);

	// Shows button sprite
	void render(SDL_Renderer* renderer);

private:
	int m_width, m_height;

	// Top left position
	SDL_Point m_position;

	Texture m_texture;

	// Button text font
	TTF_Font* p_font;

	SDL_Color m_text_colour;
};


#pragma once

#include <SDL.h>

#include "Texture.h"
#include "ButtonType.h"

class Button
{
public:
	int m_width, m_height;

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

	// Return type of button
	ButtonType type();

protected:
	

	// Top left position
	SDL_Point m_position;

	Texture m_texture;

	// Button text font
	TTF_Font* p_font;

	SDL_Color m_text_colour;

	ButtonType m_type;
};


#include "Button.h"

Button::Button()
{
	m_position.x = 0;
	m_position.y = 0;

	m_width = 0;
	m_height = 0;

	m_text_colour = { 0,0,0 };

	p_font = NULL;
}

bool Button::init(
	SDL_Renderer* renderer, 
	int x, int y, 
	std::string font_path, 
	std::string text, 
	int font_size, 
	SDL_Color text_color)
{
	bool success = true;

	m_position.x = x;
	m_position.y = y;

	m_text_colour.r = text_color.r;
	m_text_colour.g = text_color.g;
	m_text_colour.b = text_color.b;
	m_text_colour.a = text_color.a;

	p_font = TTF_OpenFont(font_path.c_str(), font_size);
	if (p_font == NULL)
	{
		printf("Failed to load font %s! SDL_ttf Error: %s\n", font_path.c_str(), TTF_GetError());
		success = false;
	}
	else
	{
		if (!m_texture.loadFromRenderedText(renderer, text, p_font, m_text_colour))
		{
			printf("Menu init() ---> Unable to load font %s\n", font_path.c_str());
			success = false;
		}
		else
		{
			m_width = m_texture.getWidth();
			m_height = m_texture.getHeight();

			// Centres position of text
			m_position.x -= m_width / 2;
		}
	}

	return success;
}

void Button::setPosition(int x, int y)
{
	m_position.x = x;
	m_position.y = y;
}

bool Button::handleEvent(SDL_Event* e)
{
	bool pressed = false;

	// If mouse event happened
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		// Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		// Check if mouse is in button
		bool inside = true;

		if (x < m_position.x){
			inside = false;
		}
		else if (x > m_position.x + m_width){
			inside = false;
		}
		else if (y < m_position.y){
			inside = false;
		}
		else if (y > m_position.y + m_height){
			inside = false;
		}

		// Mouse id outside button
		if (inside)
		{
			// Set mouse over sprite
			switch (e->type)
			{
			case SDL_MOUSEMOTION:
				break;
			case SDL_MOUSEBUTTONDOWN:
				pressed = true;
				break;
			case SDL_MOUSEBUTTONUP:
				break;
			}
		}
	}

	return pressed;
}

void Button::render(SDL_Renderer* renderer)
{
	m_texture.render(renderer, m_position.x, m_position.y);
}
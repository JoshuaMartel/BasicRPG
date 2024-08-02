#include "Menu.h"

Menu::Menu()
{
	m_window_width = 0;
	m_window_height = 0;
	m_num_sprites_width = 0;
	m_num_sprites_height = 0;
	m_image_path = "";
	m_text_colour = { 0,0,0 };
	p_font = NULL;
}

Menu::~Menu()
{
	TTF_CloseFont(p_font);
	p_font = NULL;
}

Menu::Menu(const Menu& m)
{
	m_window_width = m.m_window_width;
	m_window_height = m.m_window_height;
	m_num_sprites_width = m.m_num_sprites_width;
	m_num_sprites_height = m.m_num_sprites_height;
	m_image_path = m.m_image_path;
	m_text_colour = m.m_text_colour;
	p_font = m.p_font;
}

bool Menu::init(SDL_Renderer* renderer, int width, int height, std::string image_path, int sprite_w, int sprite_h)
{
	bool success = true;

	m_window_width = width;
	m_window_height = height;
	m_image_path = image_path;
	m_num_sprites_width = sprite_w;
	m_num_sprites_height = sprite_h;

	int const NUM_BUTTONS = 2;

	std::string font_path = "resources/SDS_8x8.ttf";
	std::string texts[NUM_BUTTONS] = { "New Game", "Exit" };
	SDL_Point positions[NUM_BUTTONS] = { 
		SDL_Point(m_window_width / 2, m_window_height / 4),
		SDL_Point(m_window_width / 2, m_window_height / 2) };

	for (int i = 0; i < NUM_BUTTONS; i++)
	{
		m_buttons.emplace_back(std::make_unique<Button>());
		if(!m_buttons.back()->init(
			renderer,
			positions[i].x,
			positions[i].y,
			font_path, texts[i],
			28,
			{ 0,0,0 }))
		{
			printf("Menu::init() ---> Failed to load %s button\n", texts[i].c_str());
			success = false;
		}
	}

	return success;
}

void Menu::render(SDL_Renderer* renderer)
{
	int size = m_buttons.size();
	if (size <= 0)
	{
		printf("Menu::render ---> Error: no buttons to render.");
	}
	else {
		for (int i = 0; i < size; i++)
		{
			m_buttons[i]->render(renderer);
		}
	}
}

//void Menu::render(SDL_Renderer* renderer, int x, int y)
//{
//	int size = m_buttons.size();
//	for (int i; i < size; i++)
//	{
//		m_buttons[i].render(renderer);
//	}
//}

bool Menu::handleEvent(SDL_Event* e)
{
	bool pressed = false;
	int size = m_buttons.size();
	for (int i = 0; i < size; i++)
	{
		pressed = m_buttons[i]->handleEvent(e);
		if (pressed)
		{

		}
	}
	return pressed;
}
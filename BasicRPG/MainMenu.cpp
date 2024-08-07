#include "MainMenu.h"

MainMenu::MainMenu(SDL_Renderer* renderer, int width, int height, std::string image_path, int sprite_w, int sprite_h) : Menu()
{
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

	m_buttons.emplace_back(std::make_unique<NewGameButton>());
	if (!m_buttons.back()->init(
		renderer,
		positions[0].x,
		positions[0].y,
		font_path, "New Game",
		28,
		{ 0,0,0 }))
	{
		throw "MainMenu() ---> Failed to create NewGame button\n";
	}

	m_buttons.emplace_back(std::make_unique<ExitButton>());
	if (!m_buttons.back()->init(
		renderer,
		positions[1].x,
		positions[1].y,
		font_path, "Exit",
		28,
		{ 0,0,0 }))
	{
		throw "MainMenu() ---> Failed to create Exit button\n";
	}

}

GameEvents MainMenu::handelEvent(SDL_Event* e)
{
	bool pressed = false;
	int size = m_buttons.size();
	GameEvents event = NOTHING;

	for (int i = 0; i < size; i++)
	{
		pressed = m_buttons[i]->handleEvent(e);
		if (pressed)
		{
			switch (m_buttons[i]->type()) {
			case NEW_GAME_BUTTON:
				event = NEW_GAME;
				break;
			case EXIT_BUTTON:
				event = EXIT;
				break;
			}
		}
	}

	return event;
}
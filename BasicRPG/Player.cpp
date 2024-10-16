#include "Player.h"

Player::Player() : Character(){}

Player::Player(int health, float x, float y, std::string name, std::vector<int> sheet_positions, SDL_Rect rec) : Character(health, x, y, name, sheet_positions, rec){}

void Player::handleKeyEvent(SDL_Event *e)
{
	switch (e->key.keysym.sym) {
	case SDLK_w:
		updatePosition(m_x, m_y - 5.0f);
		break;
	case SDLK_s:
		updatePosition(m_x, m_y + 5.0f);
		break;
	case SDLK_a:
		updatePosition(m_x - 5.0f, m_y);
		break;
	case SDLK_d:
		updatePosition(m_x + 5.0f, m_y);		
		break;
	}
}
/*
void Player::addTextures(std::vector<SpriteSheetData>* sheets, SDL_Renderer* renderer)
{
	for (auto&& sheet : *sheets)
	{
		p_textures.emplace_back(std::make_unique<SpriteSheet>(&sheet));
		p_textures.back()->loadFromFile(renderer, sheet.image_path);
	}
}
*/
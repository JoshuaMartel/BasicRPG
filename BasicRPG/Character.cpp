#include "Character.h"

Character::Character()
{
	m_health = 100;
	m_x = 0, m_y = 0;
	m_name = "Character";
}

Character::Character(int health, float x, float y, std::string name, std::vector<int> sheet_positions)
{
	m_health = health;
	m_x = x;
	m_y = y;
	m_name = name;
	m_sheet_positions = sheet_positions;
}

/*
void Character::addTextures(std::vector<std::string>* textures, SDL_Renderer* renderer)
{
	for (auto&& name : *textures)
	{
		p_textures.emplace_back(std::make_unique<Texture>());
		p_textures.back()->loadFromFile(renderer, name);
	}
}

void Character::render(SDL_Renderer* renderer)
{
	for (auto&& texture : p_textures)
	{
		texture->render(renderer, m_x, m_y);
	}
}
*/

void Character::updatePosition(float x, float y)
{
	m_x = x;
	m_y = y;
}
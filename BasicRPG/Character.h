#pragma once

#include <string>
#include <memory>
#include <vector>
#include <SDL.h>

#include "Texture.h"

class Character
{
public:
	Character();

	Character(int health, float x, float y, std::string name, std::vector<int> sheet_positions);

	// void addTextures(std::vector<std::string>* textures, SDL_Renderer* renderer);

	// void render(SDL_Renderer* renderer);

	void updatePosition(float x, float y);

public:
	int m_health;

	float m_x, m_y;

	std::vector<int> m_sheet_positions;

	std::string m_name;

protected:

	// std::vector<std::unique_ptr<Texture>> p_textures;
};


#pragma once

#include <SDL.h>
#include <string>
#include <exception>
#include <vector>

#include "Texture.h"

class GameMap
{
public:

	GameMap(SDL_Renderer* renderer, int width, int height, std::string image_path, int sprite_rows, int sprite_cols);

	void render(SDL_Renderer* renderer);

protected:

	int m_width, m_height;

	int m_sprite_rows, m_sprite_cols;

	float m_sprite_w, m_sprite_h;

	Texture m_map_texture;
};


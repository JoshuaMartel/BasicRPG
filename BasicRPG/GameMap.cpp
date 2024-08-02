#include "GameMap.h"

#include <iostream>

GameMap::GameMap(SDL_Renderer* renderer, int width, int height, std::string image_path, int sprite_rows, int sprite_cols)
{
	m_width = width;
	m_height = height;

	m_sprite_rows = sprite_rows;
	m_sprite_cols = sprite_cols;

	if (!m_map_texture.loadFromFile(renderer, image_path)) {
		throw ("Error: could not load image file " + image_path);
	}

	m_sprite_w = float(m_map_texture.getWidth()) / float(m_sprite_rows);
	m_sprite_h = float(m_map_texture.getHeight()) / float(m_sprite_cols);

	std::cout << "m_sprite_rows : " << m_sprite_rows << std::endl;
	std::cout << "m_sprite_cols : " << m_sprite_cols << std::endl;
	std::cout << "text width : " << m_map_texture.getWidth() << std::endl;
	std::cout << "text height : " << m_map_texture.getHeight() << std::endl;
	std::cout << "m_sprite_w : " << m_sprite_w << std::endl;
	std::cout << "m_sprite_h : " << m_sprite_h << std::endl;

}

void GameMap::render(SDL_Renderer* renderer)
{

}
#include "SpriteSheet.h"

#include <iostream>

SpriteSheet::SpriteSheet(int rows, int cols, int tile_set_w, int tile_set_h) :
	Texture()
{
	m_info.rows = rows;
	m_info.cols = cols;
	m_info.tile_width = 0;
	m_info.tile_height= 0;
	m_info.tile_set_w = tile_set_w;
	m_info.tile_set_h = tile_set_h;
}

SpriteSheet::SpriteSheet(SpriteSheetInfo* info) : Texture()
{
	m_info.rows = info->rows;
	m_info.cols = info->cols;

	m_info.total_tiles = m_info.rows * m_info.cols;

	m_info.tile_block_w = info->tile_block_w;
	m_info.tile_block_h = info->tile_block_h;
	m_info.tile_block_w = info->tile_block_w;
	m_info.tile_block_h = info->tile_block_h;
	m_info.skip_rows = info->skip_rows;
	m_info.skip_cols = info->skip_cols;
	m_info.tile_set_w = info->tile_set_w;
	m_info.tile_set_h = info->tile_set_h;

	// This is likely some default value and will be calculated after sheet is loaded
	m_info.tile_width = info->tile_width;
	m_info.tile_height = info->tile_height;
}

void SpriteSheet::loadFromFile(SDL_Renderer* renderer, std::string image_path)
{
	if (!Texture::loadFromFile(renderer, image_path))
	{
		throw "SpriteSheet::loadFromFile ---> Error: Could not load image " + image_path + "\n";
	}
	else
	{
		m_info.tile_width = float(m_width) / float(m_info.cols);
		m_info.tile_height = float(m_height) / float(m_info.rows);
		int max = m_info.cols;
		for (int i = 0; i < max; i++)
		{
			m_tiles.emplace_back(std::make_unique<SDL_Rect>());
			m_tiles.back()->w = m_info.tile_width;
			m_tiles.back()->h = m_info.tile_height;
			m_tiles.back()->x = m_info.tile_width * i;
			m_tiles.back()->y = m_info.tile_height * 3;
		}
	}
}

void SpriteSheet::render(SDL_Renderer* renderer)
{
	//Set rendering space and render to screen
	//SDL_Rect render_quad = { 0, 0, m_info.tile_width * 1.5, m_info.tile_height * 1.5 };
	//SDL_Rect clip = { m_tiles.front()->x, m_tiles.front()->y, m_tiles.front()->w, m_tiles.front()->h };

	//SDL_RenderCopy(renderer, m_texture, &clip, &render_quad);

	

	//////Set clip rendering dimensions
	////if (clip != NULL)
	////{
	////	render_quad.w = clip->w;
	////	render_quad.h = clip->h;
	////}
	//int i = 0, j = 0;
	//for (std::vector<std::unique_ptr<SDL_Rect>>::iterator iter = m_tiles.begin(); iter < m_tiles.end(); iter++)
	//{
	//	// The sprite sheet contains m_dims.w by m_dims.h tiles, but we store it in a linear vector
	//	if (i% m_dims.w == 0) i = 0;
	//	if (j % m_dims.h == 0) j = 0;

	//	render_quad = { 0.0, 0.0, m_sprite_dims.w * 1.5, m_sprite_dims.h * 1.5 };
	//	render_quad.x =
	//	clip = { m_tiles.back()->x, m_tiles.back()->y, m_tiles.back()->w, m_tiles.back()->h };
	//}
	SDL_Rect render_quad = { 0.0,0.0,0.0,0.0 };
	SDL_Rect clip = { 0.0,0.0,0.0,0.0 };
	int i = 0;
	int j = 0;
	for (std::vector<std::unique_ptr<SDL_Rect>>::iterator iter = m_tiles.begin(); iter < m_tiles.end(); iter++)
	{
		render_quad.x = i * m_info.tile_width;
		render_quad.y = j * m_info.tile_height;
		render_quad.w = m_info.tile_width;
		render_quad.h = m_info.tile_height;

		// Because we use unique_ptrs we cannot pass them to SDL_RenderCopy
		clip.x = (*iter)->x;
		clip.y = (*iter)->y;
		clip.w = (*iter)->w;
		clip.h = (*iter)->h;

		SDL_RenderCopy(renderer, m_texture, &(*(*iter)), &render_quad);
		//SDL_RenderCopy(renderer, m_texture, &clip, &render_quad);
		i++;
	}

	//Render to screen
	
	/*
	std::cout << "m_tiles x : " << m_tiles.back()->x << std::endl;
	std::cout << "m_tiles y: " << m_tiles.back()->y << std::endl;
	std::cout << "m_tiles w : " << m_tiles.back()->w << std::endl;
	std::cout << "m_tiles h : " << m_tiles.back()->h << std::endl;
	*/
}

int SpriteSheet::getNumRows() {
	return m_info.rows;
}

int SpriteSheet::getNumCols()
{
	return m_info.cols;
}

float SpriteSheet::getSpriteWidth()
{
	return m_info.tile_width;
}

float SpriteSheet::getSpriteHeight()
{
	return m_info.tile_height;
}

int SpriteSheet::getWidth()
{
	return m_width;
}

int SpriteSheet::getHeight()
{
	return m_height;
}
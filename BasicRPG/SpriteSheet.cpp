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

SpriteSheet::SpriteSheet(SpriteSheetData* info) : Texture()
{
	m_info.rows = info->rows;
	m_info.cols = info->cols;

	m_info.total_tiles = m_info.rows * m_info.cols;

	m_info.block_row_length = info->block_row_length;
	m_info.block_col_length = info->block_col_length;
	m_info.skip_rows = info->skip_rows;
	m_info.skip_cols = info->skip_cols;
	m_info.tile_set_w = info->tile_set_w;
	m_info.tile_set_h = info->tile_set_h;

	// This is likely some default value and will be calculated after sheet is loaded
	m_info.tile_width = info->tile_width;
	m_info.tile_height = info->tile_height;

	m_info.file_name = info->file_name;
	m_info.image_path = info->image_path;
}

void SpriteSheet::loadFromFile(SDL_Renderer* renderer)
{
	if (!Texture::loadFromFile(renderer, m_info.image_path))
	{
		throw "SpriteSheet::loadFromFile ---> Error: Could not load image " + m_info.image_path + "\n";
	}
	else
	{
		m_info.tile_width = float(m_width) / float(m_info.cols);
		m_info.tile_height = float(m_height) / float(m_info.rows);
		
		
		if (m_info.block_col_length > 0)
		{// Since we have blocks, we capture similar tiles before moving horizontally to the next block

			// Calculate block tile area
			int horizontal_blocks = m_info.cols / m_info.block_col_length;
			int vertical_blocks = m_info.rows / m_info.block_row_length;
			int cols = m_info.block_col_length;
			int rows = m_info.block_row_length;

			/*std::cout << std::endl;
			std::cout << "sheet width: " << m_width << std::endl;
			std::cout << "sheet height : " << m_height << std::endl;
			std::cout << "tile width: " << m_info.tile_width << std::endl;
			std::cout << "tile height: " << m_info.tile_height << std::endl;
			std::cout << "cols : " << m_info.cols << std::endl;
			std::cout << "rows : " << m_info.rows << std::endl;
			std::cout << "i_max : block col w : " << m_info.block_col_length << std::endl;
			std::cout << "j_max : block row h : " << m_info.block_row_length << std::endl;
			std::cout << "block_width_max : " << horizontal_blocks << std::endl;
			std::cout << "block_height_max : " << vertical_blocks << std::endl;*/
			
			for (int r = 0; r < vertical_blocks; r++)
			{
				for (int c = 0; c < horizontal_blocks; c++)
				{
					for (int j = 0; j < rows; j++)
					{
						for (int i = 0; i < cols; i++)
						{
							m_tiles.emplace_back(std::make_unique<SDL_Rect>());
							m_tiles.back()->w = m_info.tile_width;
							m_tiles.back()->h = m_info.tile_height;
							m_tiles.back()->x = m_info.tile_width * i + (c * cols * m_info.tile_width);
							m_tiles.back()->y = m_info.tile_height * j + (r * rows * m_info.tile_height);
						}
					}
				}
			}
		}
		else
		{ // There are no blocks so we captures tiles from left to right and top to bottom
			int i_max = m_info.cols;
			int j_max = m_info.rows;
			//std::cout << "cols : " << m_info.cols << std::endl;
			//std::cout << "rows : " << m_info.rows << std::endl;
			for (int j = 0; j < j_max; j++)
			{
				for (int i = 0; i < i_max; i++)
				{
					m_tiles.emplace_back(std::make_unique<SDL_Rect>());
					m_tiles.back()->w = m_info.tile_width;
					m_tiles.back()->h = m_info.tile_height;
					m_tiles.back()->x = m_info.tile_width * i;
					m_tiles.back()->y = m_info.tile_height * j;
				}
			}
		}
		//std::cout << m_info.image_path << std::endl;
		//std::cout << m_tiles.size() << std::endl;
	}
}

// renders all tiles in order
void SpriteSheet::render(SDL_Renderer* renderer)
{
	SDL_Rect render_quad = { 0.0,0.0,0.0,0.0 };
	int i = 0;
	int j = 0;
	//Set rendering space and render to screen
	for (std::vector<std::unique_ptr<SDL_Rect>>::iterator iter = m_tiles.begin(); iter < m_tiles.end(); iter++)
	{
		render_quad.x = i * m_info.tile_width;
		render_quad.y = j * m_info.tile_height;
		render_quad.w = m_info.tile_width;
		render_quad.h = m_info.tile_height;

		SDL_RenderCopy(renderer, m_texture, &(*(*iter)), &render_quad);
		//SDL_RenderCopy(renderer, m_texture, &clip, &render_quad);
		i++;
		if (i >= m_info.cols)
		{
			j++;
			i = 0;
		}
	}
}

// Renders a single tile at position (x, y)
void SpriteSheet::render(SDL_Renderer* renderer, float x, float y, int pos, float scale)
{
	SDL_Rect render_quad = { x, y, m_info.tile_width * scale, m_info.tile_height * scale };

	SDL_RenderCopy(renderer, m_texture, &(*m_tiles[pos]), &render_quad);
}

void SpriteSheet::render(SDL_Renderer* renderer, std::vector<std::vector<int>> *tiles, float scale)
{
	SDL_Rect quad = { 0.0,0.0,0.0,0.0 };
	int i = 0, j = 0;

	//Render to screen
	for (auto& row : *tiles)
	{
		for (auto tile : row)
		{
			quad.x = i * m_info.tile_width * scale;
			quad.y = j * m_info.tile_height * scale;
			quad.w = m_info.tile_width * scale;
			quad.h = m_info.tile_height * scale;

			SDL_RenderCopy(renderer, m_texture, &(*m_tiles[tile-1]), &quad);
			
			i++;
		}
		i = 0;
		j++;
	}
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
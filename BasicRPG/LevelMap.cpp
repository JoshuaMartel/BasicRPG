#include "LevelMap.h"

LevelMap::LevelMap(SDL_Renderer* renderer, int width, int height, std::string image_path, int sprite_rows, int sprite_cols) :
	GameMap(renderer, width, height, image_path, sprite_rows, sprite_cols)
{
	// The first 3 rows are only colour pallets and sprite orientation guides, so we will skip them here
	int skip_section = m_sprite_cols * 3 - 1;
	int const NUM_SPRITES = 9;
	int max = skip_section + NUM_SPRITES;

	for (int i = 0; i < NUM_SPRITES; i++)
	{

	}
}
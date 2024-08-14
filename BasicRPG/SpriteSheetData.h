#pragma once
#include <memory>
#include <string>

struct SpriteSheetData
{
	int rows = 0, cols = 0;
	int total_tiles = 0;

	// Individual tile dimensions
	float tile_width = 0.0, tile_height = 0.0;

	// A group of tiles of similar style or texture
	float tile_set_w = 0.0, tile_set_h = 0.0;

	// A block is a group of sets of tiles that are common to each other in some way
	// i.e. sets of brick tiles of different colours
	int block_row_length = 0, block_col_length = 0;

	// Skip empty sections of the sprite sheet. Are to be used as a matrix, so for example,
	// skips rows 4-8 at coloumns 6-9
	std::tuple<int, int> skip_rows = std::make_tuple(0.0, 0.0), skip_cols = std::make_tuple(0.0, 0.0);

	std::string image_path = "";
	std::string file_name = "";
};
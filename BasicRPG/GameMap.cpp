#include "GameMap.h"
/// <summary>
/// Assumes that each terrain tiles is of the same dimensions across different sheets.
/// </summary>
/// <param name="renderer"></param>
/// <param name="width"></param>
/// <param name="height"></param>
/// <param name="sheet_data"></param>
/// <param name="t_data"></param>
GameMap::GameMap(SDL_Renderer* renderer, int width, int height,
	std::vector<std::unique_ptr<SpriteSheetData>>* sheet_data, std::unique_ptr<TerrainData>* t_data, float scale)
{
	m_width = width;
	m_height = height;
	m_scale = scale;
	p_terrain_data = std::make_unique<TerrainData>();

	try {
		for (auto&& d : *sheet_data)
		{
			if (d == NULL)
				throw "d is NULL from sheet_data\n";
			
			p_sheet[d->file_name] = (std::make_unique<SpriteSheet>(&(*d)));
			p_sheet[d->file_name]->loadFromFile(renderer);			
		}
		// Get the sprite dimensions. This implies that all terrain tiles are the of same dimensions
		m_tWidth = p_sheet[(*sheet_data).front()->file_name]->getSpriteWidth();
		m_tHeight = p_sheet[(*sheet_data).front()->file_name]->getSpriteHeight();

		p_terrain_data->name = (*t_data)->name;
		p_terrain_data->map_size = (*t_data)->map_size;

		for (auto& t : (*t_data)->map)
		{
			p_terrain_data->map.emplace_back(std::make_unique<Terrain>());
			p_terrain_data->map.back()->cols = t->cols;
			p_terrain_data->map.back()->rows = t->rows;
			p_terrain_data->map.back()->sheet_name = t->sheet_name;
			p_terrain_data->map.back()->layers = t->layers;
		}
		int rows = (*t_data)->wall_grid.size(), cols = (*t_data)->wall_grid.back().size();
		for (auto& r : (*t_data)->wall_grid)
		{
			std::vector<int> vec;
			for (auto c : r)
			{
				vec.emplace_back(c);
			}
			m_walls.emplace_back(vec);
		}
		
	}
	catch (std::string e)
	{
		throw e;
	}
}

//GameMap::GameMap(SDL_Renderer* renderer, int width, int height,
//	std::vector<std::unique_ptr<SpriteSheetData>>* sheet_data, std::vector<std::unique_ptr<TerrainData>>* t_data)
//{
//	m_width = width;
//	m_height = height;
//
//	try {
//		for (auto&& d : *sheet_data)
//		{
//			if (d == NULL)
//				throw "d is NULL from sheet_data\n";
//
//			p_sheet[d->file_name] = (std::make_unique<SpriteSheet>(&(*d)));
//			p_sheet[d->file_name]->loadFromFile(renderer);
//		}
//		for (auto&& d : *t_data)
//		{
//			if (d == NULL)
//				throw "t_data member is NULL\n";
//			p_terrain_data.emplace_back(std::make_unique<TerrainData>());
//			p_terrain_data.back()->name = d->name;
//			for (auto&& t : d->map)
//			{
//				p_terrain_data.back()->map.emplace_back(std::make_unique<Terrain>());
//				p_terrain_data.back()->map.back()->cols = t->cols;
//				p_terrain_data.back()->map.back()->rows = t->rows;
//				p_terrain_data.back()->map.back()->sheet_name = t->sheet_name;
//				p_terrain_data.back()->map.back()->layers = t->layers;
//			}
//		}
//	}
//	catch (std::string e)
//	{
//		throw e;
//	}
//}

void GameMap::render(SDL_Renderer* renderer)
{
	// check for NULL
	if (p_terrain_data == NULL)
		throw "terrain data is NULL\n";

	for (auto&& terrain : p_terrain_data->map)
	{
		if (terrain == NULL)
			throw "terrain struct is NULL\n";
		p_sheet[terrain->sheet_name]->render(renderer, &terrain->layers, m_scale);
	}
}

/// <summary>
/// Checks if coords are within a wall tile and changes x and y to the closest point outside of the wall.
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
void GameMap::moveAwayFromWall(float* x, float* y)
{
	int col = (int)std::floorf(*x / (m_tWidth * m_scale));
	int row = (int)std::floorf(*y / (m_tHeight * m_scale));
	SDL_Rect wall;
	wall.w = m_tWidth;
	wall.h = m_tHeight;
	//wall.

	//if(wallCollision())
	//float x0 = *x;
	//float y0 = *y;
	//int col = 0, row = 0;
	//int *c = &col, *r = &row;
	////printf("player coords before: x, y : %f, %f\n", *x, *y);
	//if (wallCollision(x0, y0, c, r))
	//{
	//	if(c != NULL && r != NULL)
	//		printf("row, col : %d, %d\n", row, col);
	//	float px = col * m_tWidth * m_scale;
	//	float py = row * m_tHeight * m_scale;
	//	printf(" px, py : %f, %f\n", px, py);
	//	// Since we are doing floating pointing comparison, there should never be an occurance of x0 = px or y0 = py
	//	if (x0 - px < 0.5)
	//		*x = px;
	//	else if (x0 - px > 0.5)
	//		*x = px + m_tWidth * m_scale;

	//	if (y0 - py < 0.5)
	//		*y = py;
	//	else if (y0 - py > 0.5)
	//		*y = py + m_tHeight * m_scale;
	//	printf("player coords after: x, y : %f, %f\n", *x, *y);
	//}


}

/// <summary>
/// Checks if x and y are within a wall tile. Col and row are optional, and will return the tile atlas row and col.
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="col"></param>
/// <param name="row"></param>
/// <returns></returns>
bool GameMap::wallCollision(float x, float y, int *col, int *row)
{
	int col0 = (int)std::floorf(x / (m_tWidth * m_scale));
	int row0 = (int)std::floorf(y / (m_tHeight * m_scale));
	//printf("player coords: x, y : %f, %f\n", x, y);
	printf("tile number: row, col : %d, %d\n", row0, col0);
	//printf("tile width/hight: %f, %f\n", m_tWidth * m_scale, m_tHeight * m_scale);
	if (row0 >= m_walls.size() || col0 >= m_walls.front().size()) {
		throw ("m_walls index out of bounds: given row, col: %d, %d while actual sizes are: row, col: %d, %d\n", row0, col0, (int)m_walls.size(), (int)m_walls.front().size());
	}
	printf("tile value:  %d\n", m_walls[row0][col0]);
	if (col != NULL)
		*col = col0;
	if (row != NULL)
		*row = row0;
	
	//printf("row0, col0 : %d, %d\n", row0, col0);
	//printf("row, col : %d, %d\n", *row, *col);
	return m_walls[row0][col0];
}

bool GameMap::wallCollision(SDL_Rect rec1, SDL_Rect rec2)
{
	// The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	// Calculate the sides of rect A
	leftA = rec1.x;
	rightA = rec1.x + rec1.w;
	topA = rec1.y;
	bottomA = rec1.y = rec1.h;

	// Calculate the sides of rect B
	leftB = rec2.x;
	rightB = rec2.x + rec2.w;
	topB = rec2.y;
	bottomB = rec2.y = rec2.h;

	// If any of the sides from A are outside of B
	if (bottomA <= topB)
		return false;
	if (topA >= bottomB)
		return false;
	if (rightA <= leftB)
		return false;
	if (leftA >= rightB)
		return false;

	// If none of the sides from A are outside B
	return true;
}

float GameMap::getTileWidth()
{
	return m_tWidth;
}

float GameMap::getTileHeight()
{
	return m_tHeight;
}

int GameMap::getRows()
{
	return p_terrain_data->rows;
}

int GameMap::getCols()
{
	return p_terrain_data->cols;
}
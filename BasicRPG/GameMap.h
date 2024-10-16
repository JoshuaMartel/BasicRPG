#pragma once

#include <SDL.h>
#include <string>
#include <exception>
#include <vector>
#include <map>
#include <memory>
#include <cmath>

#include "Texture.h"
#include "SpriteSheet.h"
#include "SpriteSheetData.h"
#include "TerrainData.h"

class GameMap
{
public:
	GameMap(SDL_Renderer* renderer, int width, int height, 
		std::vector<std::unique_ptr<SpriteSheetData>>* sheet_data, std::unique_ptr<TerrainData>* t_data, float scale = 1.0);

	GameMap(SDL_Renderer* renderer, int width, int height, 
		std::vector<std::unique_ptr<SpriteSheetData>>* sheet_data, std::vector<std::unique_ptr<TerrainData>>* t_data);

	void render(SDL_Renderer* renderer);

	void moveAwayFromWall(float *x, float *y);

	bool wallCollision(float x, float y, int *col = NULL, int *row = NULL);

	bool wallCollision(SDL_Rect rec1, SDL_Rect rec2);

	float getTileWidth();

	float getTileHeight();

	int getRows();

	int getCols();

protected:
	int m_width, m_height;

	float m_tWidth, m_tHeight, m_scale;

	std::map<std::string, std::unique_ptr<SpriteSheet>> p_sheet;

	std::unique_ptr<TerrainData> p_terrain_data;

	std::vector<std::vector<int>> m_walls;
};


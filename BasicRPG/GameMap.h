#pragma once

#include <SDL.h>
#include <string>
#include <exception>
#include <vector>
#include <map>
#include <memory>

#include "Texture.h"
#include "SpriteSheet.h"
#include "SpriteSheetData.h"
#include "TerrainData.h"

class GameMap
{
public:
	GameMap(SDL_Renderer* renderer, int width, int height, SpriteSheetData* info);

	GameMap(SDL_Renderer* renderer, int width, int height, 
		std::vector<std::unique_ptr<SpriteSheetData>>* sheet_data, std::vector<std::unique_ptr<TerrainData>>* t_data);

	void render(SDL_Renderer* renderer);

protected:
	int m_width, m_height;

	std::map<std::string, std::unique_ptr<SpriteSheet>> p_sheet;

	std::vector<std::unique_ptr<TerrainData>> p_terrain_data;
};


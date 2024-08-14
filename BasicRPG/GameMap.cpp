#include "GameMap.h"

#include <iostream>

GameMap::GameMap(SDL_Renderer* renderer, int width, int height, SpriteSheetData* info)
{
	m_width = width;
	m_height = height;

	p_sheet[info->file_name] = (std::make_unique<SpriteSheet>(info));

	try {
		p_sheet[info->file_name]->loadFromFile(renderer, info->image_path);
	}
	catch(std::string e)
	{
		throw e;
	}
}

GameMap::GameMap(SDL_Renderer* renderer, int width, int height,
	std::vector<std::unique_ptr<SpriteSheetData>>* sheet_data, std::vector<std::unique_ptr<TerrainData>>* t_data)
{
	m_width = width;
	m_height = height;

	try {
		for (auto&& d : *sheet_data)
		{
			p_sheet[d->file_name] = (std::make_unique<SpriteSheet>(&(*d)));
			p_sheet[d->file_name]->loadFromFile(renderer, d->image_path);
		}
		for (auto&& d : *t_data)
		{
			p_terrain_data.emplace_back(std::make_unique<TerrainData>());
			p_terrain_data.back()->name = d->name;
			for (auto&& t : d->map)
			{
				p_terrain_data.back()->map.emplace_back(std::make_unique<Terrain>());
				p_terrain_data.back()->map.back()->cols = t->cols;
				p_terrain_data.back()->map.back()->rows = t->rows;
				p_terrain_data.back()->map.back()->sheet_name = t->sheet_name;
				p_terrain_data.back()->map.back()->layers = t->layers;
			}

			
		}

	}
	catch (std::string e)
	{
		throw e;
	}
}

void GameMap::render(SDL_Renderer* renderer)
{
	for (auto&& data : p_terrain_data)
	{
		for (auto&& terrain : data->map)
		{
			p_sheet[terrain->sheet_name]->render(renderer, &terrain->layers);
		}
	}
}
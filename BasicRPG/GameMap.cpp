#include "GameMap.h"

#include <iostream>

GameMap::GameMap(SDL_Renderer* renderer, int width, int height, SpriteSheetData* info)
{
	m_width = width;
	m_height = height;

	p_sheet.emplace_back(std::make_unique<SpriteSheet>(info));

	try {
		p_sheet.back()->loadFromFile(renderer, info->image_path);
	}
	catch(std::string e)
	{
		throw e;
	}
}

GameMap::GameMap(SDL_Renderer* renderer, int width, int height, std::vector<std::unique_ptr<SpriteSheetData>>* data)
{
	m_width = width;
	m_height = height;

	//p_sheet = std::make_unique<SpriteSheet>(data);

	try {
		for (const std::unique_ptr<SpriteSheetData>& d : *data)
		{
			p_sheet.emplace_back(std::make_unique<SpriteSheet>(&(*d)));
			p_sheet.back()->loadFromFile(renderer, d->image_path);
		}
	}
	catch (std::string e)
	{
		throw e;
	}
}

void GameMap::render(SDL_Renderer* renderer)
{

}
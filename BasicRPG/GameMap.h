#pragma once

#include <SDL.h>
#include <string>
#include <exception>
#include <vector>
#include <memory>

#include "Texture.h"
#include "SpriteSheet.h"
#include "SpriteSheetData.h"

class GameMap
{
public:
	GameMap(SDL_Renderer* renderer, int width, int height, SpriteSheetData* info);

	GameMap(SDL_Renderer* renderer, int width, int height, std::vector<std::unique_ptr<SpriteSheetData>>* info);

	void render(SDL_Renderer* renderer);

protected:
	int m_width, m_height;

	std::vector<std::unique_ptr<SpriteSheet>> p_sheet;
};


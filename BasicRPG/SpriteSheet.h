#pragma once
#include <vector>
#include <memory>

#include "SpriteSheetData.h"
#include "Texture.h"
#include "Square.h"

class SpriteSheet : public Texture
{
public:
	SpriteSheet(int rows, int cols, int tile_set_w, int tile_set_h);

	SpriteSheet(SpriteSheetData* info);

	void loadFromFile(SDL_Renderer* renderer, std::string);

	int getNumRows();

	int getNumCols();

	float getSpriteWidth();

	float getSpriteHeight();

	int getWidth();

	int getHeight();

	void render(SDL_Renderer* renderer);

	void render(SDL_Renderer* renderer, std::vector<std::vector<int>>* tiles);

private:
	SpriteSheetData m_info;

	std::vector<std::unique_ptr<SDL_Rect>> m_tiles;

};
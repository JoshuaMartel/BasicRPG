#pragma once
#include <vector>
#include <memory>

#include "SpriteSheetInfo.h"
#include "Texture.h"
#include "Square.h"

class SpriteSheet : public Texture
{
public:
	SpriteSheet(int rows, int cols, int tile_set_w, int tile_set_h);

	SpriteSheet(SpriteSheetInfo* info);

	void loadFromFile(SDL_Renderer* renderer, std::string);

	int getNumRows();

	int getNumCols();

	float getSpriteWidth();

	float getSpriteHeight();

	int getWidth();

	int getHeight();

	void render(SDL_Renderer* renderer);

private:
	SpriteSheetInfo m_info;

	std::vector<std::unique_ptr<SDL_Rect>> m_tiles;

};
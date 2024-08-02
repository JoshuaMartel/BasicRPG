#pragma once
#include "GameMap.h"

#include <memory>

class LevelMap : 
    public GameMap
{
public:

    LevelMap(SDL_Renderer* renderer, int width, int height, std::string image_path, int sprite_rows, int sprite_cols);

private:

};


#pragma once
#include "GameMap.h"

#include <memory>

class LevelMap : 
    public GameMap
{
public:

    LevelMap(SDL_Renderer* renderer, int width, int height, SpriteSheetData* info);

private:

};


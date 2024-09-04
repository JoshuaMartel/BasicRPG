#pragma once
#include "Character.h"
#include "SpriteSheet.h"

class Player :
    public Character
{
public:
    Player();

    Player(int health, float x, float y, std::string name, std::vector<int> sheet_positions);

    void handleKeyEvent(SDL_Event e);

    // void addTextures(std::vector<SpriteSheetData>* sheets, SDL_Renderer* renderer);

private:

    // std::vector<std::unique_ptr<SpriteSheet>> p_textures;
};


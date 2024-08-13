// BasicRPG.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <SDL.h>
#include <SDL_image.h>
#include <string>

#include "Game.h"
#include "FileHandler.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int argc, char* args[])
{
    // Testing file handler. Remove when done.
    // ****
    try {
        TerrainData mapTest;
        mapTest.name = "Test_Map.txt";
        mapTest.map.emplace_back(std::make_unique<Terrain>());
        mapTest.map.back()->layers = 
        { 
            {1,1,1,1,1},
            {1,0,0,0,1},
            {1,1,0,0,0,}
        };
        mapTest.map.back()->rows = mapTest.map.back()->layers.size();
        mapTest.map.back()->cols = mapTest.map.back()->layers.front().size();

        /*mapTest.map.emplace_back(std::make_unique<Terrain>());
        mapTest.map.back()->layers =
        {
            {2,1,1,1,2},
            {1,0,0,0,1},
            {1,0,0,0,1,},
            {2,1,1,1,2}
        };
        mapTest.map.back()->rows = mapTest.map.back()->layers.size();
        mapTest.map.back()->cols = mapTest.map.back()->layers.front().size();*/
        file::saveMap(&mapTest);

        //Test MapInfo::print()
        // ****
        mapTest.print();
        // ****
    }
    catch (std::string e)
    {
        printf(e.c_str());
        return -1;
    }
    TerrainData loadTest;
    file::loadMap("maps/Test_Map.txt", &loadTest);
    loadTest.print();
    // ****
    
    Game game(SCREEN_WIDTH, SCREEN_HEIGHT);

    game.init();
    game.loop();
    game.close();

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

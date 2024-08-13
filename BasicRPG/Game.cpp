#include "Game.h"

// remove after testing
// ***
#include "SpriteSheet.h"
#include "Constants.h"
// ***

Game::Game(int window_width, int window_height)
{
	m_window_width = window_width;
	m_window_height = window_height;
}

Game::~Game()
{
	close();
}

bool Game::init()
{
	// Initialisation flag
	bool success = true;

	// Initialise SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Game.init ---> SDL could not initialise. SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Game.init ---> Warning: Linear texture filtering not enabled!");
		}

		// Create window
		m_window = SDL_CreateWindow("Main Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_window_width, m_window_height, SDL_WINDOW_SHOWN);
		if (m_window == NULL)
		{
			printf("Game.init ---> SDL could not create main menu window. SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
			if (m_renderer == NULL)
			{
				printf("Game.init ---> Renderer could not be created. SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				// Initialise renderer colour
				SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					printf("Game.init ---> SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("Game.init ---> SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
				else
				{
					try {
						p_main_menu = std::make_unique<MainMenu>(m_renderer, m_window_width, m_window_height, "resources/Wall.png", WALL_SHEET_ROWS, WALL_SHEET_COLS);
					}
					catch (std::string e)
					{
						printf("Game.init ---> Menu class could not initialize! Error\n");
						success = false;
					}
				}
			}
		}
	}

	return success;
}

void Game::loop()
{
	bool quit = false, playing = false;
	// Remove after testing GameMap
	// ****
	int rows = FLOOR_SHEET_ROWS, cols = FLOOR_SHEET_COLS;
	SpriteSheetData info = { rows, cols, 0, 0.0, 0.0, 0.0, 0.0, 3, 7 };
	//SpriteSheet sheet(rows, cols, 7, 7);
	SpriteSheet sheet(&info);
	sheet.loadFromFile(m_renderer, "resources/Floor.png");
	// ****

	SDL_Event e;
	try {
		GameMap game_map(m_renderer, m_window_width, m_window_height, &info);
	}
	catch (std::string e)
	{
		printf(e.c_str());
	}
	// Remove after testing SpriteSheet 
	// ****
	

	rows = WALL_SHEET_ROWS; cols = WALL_SHEET_COLS;
	SpriteSheetData info2 = { rows, cols, 0, 0.0, 0.0, 0.0, 0.0, 3, 7 };
	SpriteSheet walls(&info2);
	walls.loadFromFile(m_renderer, "resources/Wall.png");
	// ****
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0 && !quit)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(m_renderer);
			
			if (!playing)
			{
				p_main_menu->render(m_renderer);

				switch (p_main_menu->handelEvent(&e)) {
				case NEW_GAME:
					playing = true;
					break;
				case EXIT:
					printf("exit pressed\n");
					quit = true;
					break;
				}
			}
			else
			{
				//sheet.render(m_renderer);
				walls.render(m_renderer);
			}

			SDL_RenderPresent(m_renderer);
		}
	}
}

void Game::close()
{
	// Free loaded images

	// Destroy window
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	m_window = NULL;
	m_renderer = NULL;

	// Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
#include "Game.h"

// remove after testing
// ***
#include "SpriteSheet.h"
// ***

Game::Game(int window_width, int window_height)
{
	m_window_width = window_width;
	m_window_height = window_height;
	m_window = NULL;
	m_renderer = NULL;
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
		throw std::string("Game.init ---> SDL could not initialise. SDL Error: \n", SDL_GetError());

	//Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		throw "Game.init ---> Warning: Linear texture filtering not enabled!";

	// Create window
	m_window = SDL_CreateWindow("Main Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_window_width, m_window_height, SDL_WINDOW_SHOWN);
	if (m_window == NULL)
		throw std::string("Game.init ---> SDL could not create main menu window. SDL Error: %s\n", SDL_GetError());
	
	// Create renderer
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	if (m_renderer == NULL)
		throw std::string("Game.init ---> Renderer could not be created. SDL Error: %s\n", SDL_GetError());

	// Initialise renderer colour
	SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	//Initialize SDL_ttf
	if (TTF_Init() == -1)
		throw std::string("Game.init ---> SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
		throw std::string("Game.init ---> SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());

	try {
		p_main_menu = std::make_unique<MainMenu>(m_renderer, m_window_width, m_window_height, "resources/Wall.png", WALL_SHEET_ROWS, WALL_SHEET_COLS);
	}
	catch (std::string e)
	{
		printf(e.c_str());
		throw "Game.init ---> Menu class could not initialize! Error\n";
	}

	return success;
}

void Game::loop()
{
	bool quit = false, playing = false;
	std::vector<std::unique_ptr<SpriteSheetData>> sheets;
	std::vector < std::unique_ptr<TerrainData>> terrain;
	// Remove after testing GameMap
	// ****
	int rows = FLOOR_SHEET_ROWS, cols = FLOOR_SHEET_COLS;
	SpriteSheetData info = { rows, cols, 0, 0.0, 0.0, 0.0, 0.0, 3, 7 ,
		std::make_tuple(0.0, 0.0), std::make_tuple(0.0, 0.0), "resources/Floor.png", "Floor.png"};

	//SpriteSheet sheet(rows, cols, 7, 7);
	sheets.emplace_back(std::make_unique<SpriteSheetData>(info));
	//SpriteSheet sheet(&info);
	//sheets.back()->loadFromFile(m_renderer, "resources/Floor.png");
	
	rows = WALL_SHEET_ROWS; cols = WALL_SHEET_COLS;
	SpriteSheetData info2 = { rows, cols, 0, 0.0, 0.0, 0.0, 0.0, 3, 7 };
	SpriteSheet walls(&info2);

	//walls.loadFromFile(m_renderer, "resources/Wall.png");

	terrain.emplace_back(std::make_unique<TerrainData>());
	file::loadMap("maps/Level_1.txt", &terrain.back());
	// ****
	SpriteSheetData info3 = { 15, 8, 0, 0.0, 0.0, 0.0, 0.0, 0, 0 ,
		std::make_tuple(0.0, 0.0), std::make_tuple(0.0, 0.0), "resources/Player0.png", "Player0.png" };
	SpriteSheet char_sheet_0(&info3);

	SpriteSheetData info4 = { 15, 8, 0, 0.0, 0.0, 0.0, 0.0, 0, 0 ,
		std::make_tuple(0.0, 0.0), std::make_tuple(0.0, 0.0), "resources/Player1.png", "Player1.png" };

	SpriteSheet char_sheet_1(&info4);

	std::vector<int> player_sheet_positions = {26,26};
	Player player(100, m_window_width / 2, m_window_height / 2, "Player 1", player_sheet_positions);

	char_sheet_0.loadFromFile(m_renderer);
	char_sheet_1.loadFromFile(m_renderer);

	SDL_Event e;

	p_cur_map = std::make_unique<GameMap>(m_renderer, m_window_width, m_window_height, &sheets, &terrain);

	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0 && !quit)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			//SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			//SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
				
			if (!playing)
			{
				SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(m_renderer);
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
				SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
				SDL_RenderClear(m_renderer);
				//sheet.render(m_renderer);
				p_cur_map->render(m_renderer);

				player.handleKeyEvent(e);

				char_sheet_0.render(m_renderer, player.m_x, player.m_y, player.m_sheet_positions[0]);
				//char_sheet_1.render(m_renderer);
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
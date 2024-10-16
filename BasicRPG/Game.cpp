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
	//p_error_callback = &error_callback;
}

Game::~Game()
{
	close();
}

bool Game::initSDL()
{
	// Initialise SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw std::string("Game.init ---> SDL could not initialise. SDL Error: \n", SDL_GetError());

	//Use OpenGL 3.1 core
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	//SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	//SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	//SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	//SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	//SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		throw "Game.init ---> Warning: Linear texture filtering not enabled!";

	// Create window
	m_window = SDL_CreateWindow("Main Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_window_width, m_window_height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (m_window == NULL)
		throw std::string("Game.init ---> SDL could not create main menu window. SDL Error: %s\n", SDL_GetError());
	
	// Create GL context
	m_context = SDL_GL_CreateContext(m_window);
	if (m_context == NULL)
		throw std::string("Game.init ---> OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
	
	//Initialize GLEW
	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
		return false;
	}

	//Use Vsync
	if (SDL_GL_SetSwapInterval(1) < 0)
	{
		printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
	}

	//Initialize OpenGL
	if (!initGL())
	{
		printf("Unable to initialize OpenGL!\n");
		return false;
	}

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

	return true;
}

bool Game::initGL()
{
	//Success flag
	bool success = true;

	// Initilise Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, m_window_width, m_window_height, 0.0, 1.0, -1.0);

	// Initialise ModelView Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Initialise clear colour
	glClearColor(0.f, 0.f, 0.f, 1.f);

	// Chech for error
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf("Error initializing OpenGL! %s\n", glGetString(error));
		return false;
	}

	//Generate program
	m_programID = glCreateProgram();

	//Create vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//Get vertex source
	const GLchar* vertexShaderSource[] =
	{
		"#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"
	};

	//Set vertex source
	glShaderSource(vertexShader, 1, vertexShaderSource, NULL);

	//Compile vertex source
	glCompileShader(vertexShader);

	//Check vertex shader for errors
	GLint vShaderCompiled = GL_FALSE;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);
	if (vShaderCompiled != GL_TRUE)
	{
		printf("Unable to compile vertex shader %d!\n", vertexShader);
		//printShaderLog(vertexShader);
		success = false;
	}
	else
	{
		//Attach vertex shader to program
		glAttachShader(m_programID, vertexShader);


		//Create fragment shader
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		//Get fragment source
		const GLchar* fragmentShaderSource[] =
		{
			"#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 1.0, 1.0, 1.0 ); }"
		};

		//Set fragment source
		glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);

		//Compile fragment source
		glCompileShader(fragmentShader);

		//Check fragment shader for errors
		GLint fShaderCompiled = GL_FALSE;
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled);
		if (fShaderCompiled != GL_TRUE)
		{
			printf("Unable to compile fragment shader %d!\n", fragmentShader);
			printShaderLog(fragmentShader);
			success = false;
		}
		else {
			//Attach fragment shader to program
			glAttachShader(m_programID, fragmentShader);


			//Link program
			glLinkProgram(m_programID);

			//Check for errors
			GLint programSuccess = GL_TRUE;
			glGetProgramiv(m_programID, GL_LINK_STATUS, &programSuccess);
			if (programSuccess != GL_TRUE)
			{
				printf("Error linking program %d!\n", m_programID);
				printProgramLog(m_programID);
				success = false;
			}
			else {
				//Get vertex attribute location
				m_vertexPos2DLocation = glGetAttribLocation(m_programID, "LVertexPos2D");
				if (m_vertexPos2DLocation == -1)
				{
					printf("LVertexPos2D is not a valid glsl program variable!\n");
					success = false;
				}
				else {
					//Initialize clear color
					glClearColor(0.f, 0.f, 0.f, 1.f);
				}
			}
		}
	}

	return true;
}

bool Game::init() {
	return initSDL();
}

void Game::printProgramLog(GLuint program)
{
	//Make sure name is shader
	if (glIsProgram(program))
	{
		//Program log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		//Get info string length
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		//Allocate string
		char* infoLog = new char[maxLength];

		//Get info log
		glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
		if (infoLogLength > 0)
		{
			//Print Log
			printf("%s\n", infoLog);
		}

		//Deallocate string
		delete[] infoLog;
	}
	else
	{
		printf("Name %d is not a program\n", program);
	}
}

void Game::printShaderLog(GLuint shader)
{
	//Make sure name is shader
	if (glIsShader(shader))
	{
		//Shader log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		//Get info string length
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		//Allocate string
		char* infoLog = new char[maxLength];

		//Get info log
		glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
		if (infoLogLength > 0)
		{
			//Print Log
			printf("%s\n", infoLog);
		}

		//Deallocate string
		delete[] infoLog;
	}
	else
	{
		printf("Name %d is not a shader\n", shader);
	}
}

/// <summary>
/// Should be called after rendering
/// </summary>
void Game::handleEntities(SDL_Event *e)
{
	p_player->handleKeyEvent(e);

	if (p_cur_map->wallCollision(p_player->m_x, p_player->m_y))
	{
		printf("player collided with wall\n");
		p_cur_map->moveAwayFromWall(&p_player->m_x, &p_player->m_y);
	}
		
}

void Game::loop()
{
	bool quit = false, playing = false, debug_enabled = true;
	std::vector<std::unique_ptr<SpriteSheetData>> sheets;
	std::unique_ptr<TerrainData> terrain;
	terrain = std::make_unique<TerrainData>();
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
	SpriteSheetData info2 = { rows, cols, 0, 0.0, 0.0, 0.0, 0.0, 0, 0,
		std::make_tuple(0.0, 0.0), std::make_tuple(0.0, 0.0), "resources/Wall.png", "Wall.png" };
	sheets.emplace_back(std::make_unique<SpriteSheetData>(info2));
	//SpriteSheet walls(&info2);

	//walls.loadFromFile(m_renderer, "resources/Wall.png");

	//terrain.emplace_back(std::make_unique<TerrainData>());

	file::loadMap("maps/Level_1.txt", &terrain);

	//terrain.front()->print();
	// ****
	SpriteSheetData info3 = { 15, 8, 0, 0.0, 0.0, 0.0, 0.0, 0, 0 ,
		std::make_tuple(0.0, 0.0), std::make_tuple(0.0, 0.0), "resources/Player0.png", "Player0.png" };
	SpriteSheet char_sheet_0(&info3);

	SpriteSheetData info4 = { 15, 8, 0, 0.0, 0.0, 0.0, 0.0, 0, 0 ,
		std::make_tuple(0.0, 0.0), std::make_tuple(0.0, 0.0), "resources/Player1.png", "Player1.png" };

	SpriteSheet char_sheet_1(&info4);

	std::vector<int> player_sheet_positions = {26,26};
	SDL_Rect rec = {0,0,0,0};
	p_player = std::make_unique<Player>(100, m_window_width / 2, m_window_height / 2, "Player 1", player_sheet_positions, rec);
	//Player player(100, m_window_width / 2, m_window_height / 2, "Player 1", player_sheet_positions);

	char_sheet_0.loadFromFile(m_renderer);
	char_sheet_1.loadFromFile(m_renderer);

	SDL_Event e;
	p_cur_map = std::make_unique<GameMap>(m_renderer, m_window_width, m_window_height, &sheets, &terrain, 1.5);

	Debug debug(m_window_width, m_window_height, p_cur_map->getTileWidth(), p_cur_map->getTileHeight(), p_cur_map->getRows(), p_cur_map->getCols());

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

			// Clear colour buffer
			glClear(GL_COLOR_BUFFER_BIT);
			// Reset modelview matrix
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			SDL_GetKeyboardState(NULL);
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

				if (debug_enabled)
				{
					//Bind program
					glUseProgram(m_programID);

					//Enable vertex position
					glEnableVertexAttribArray(m_vertexPos2DLocation);

					for (auto vao : debug.getVAOs())
					{
						glBindVertexArray(vao);
						glDrawElements(GL_LINE, 2, GL_UNSIGNED_INT, NULL);
					}

					//Disable vertex position
					glDisableVertexAttribArray(m_vertexPos2DLocation);

					//Unbind program
					glUseProgram(NULL);
				}
				SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
				SDL_RenderClear(m_renderer);
				//sheet.render(m_renderer);
				p_cur_map->render(m_renderer);

				handleEntities(&e);

				char_sheet_0.render(m_renderer, p_player->m_x + (char_sheet_0.getSpriteWidth() * 0.5), p_player->m_y + (char_sheet_0.getSpriteHeight() * 0.5), p_player->m_sheet_positions[0]);
				//char_sheet_1.render(m_renderer);
			}
			
			SDL_RenderPresent(m_renderer);

			//SDL_GL_SwapWindow(m_window);
		}
	}
}

void Game::close()
{
	glDeleteProgram(m_programID);

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
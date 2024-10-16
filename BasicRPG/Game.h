#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <gl/glew.h>
#include <gl/GL.h>
#include <SDL_opengl.h>
#include <stdio.h>
#include <memory>
#include <exception>

#include "MainMenu.h"
#include "Constants.h"
#include "GameMap.h"
#include "FileHandler.h"
#include "Player.h"
#include "Debug.h"
#include "call_back.h"

class Game
{
public:
	Game(int window_width, int window_height);

	~Game();

	bool init();

	bool initSDL();

	bool initGL();

	void loop();

	void close();

	void handleEntities(SDL_Event *e);

	void printProgramLog(GLuint program);

	void printShaderLog(GLuint shader);

private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	//OpenGL context
	SDL_GLContext m_context;

	GLuint m_programID = 0;
	GLint m_vertexPos2DLocation = -1;

	std::unique_ptr<MainMenu> p_main_menu;

	std::unique_ptr<GameMap> p_cur_map;

	std::unique_ptr<Player> p_player;

	int m_window_width;
	int m_window_height;
};


#include "Debug.h"

Debug::Debug(int screenW, int screenH, float w, float h, int r, int c) : 
	screen_w(screenW), screen_h(screenH), tile_width(w), tile_height(h), rows(r), cols(c)
{
	// Horizontal lines
	for (int i = 0; i < rows; i++)
	{
		GLfloat vertextData[] = {
			0.f,				i * tile_height,
			cols * tile_width,	i * tile_height
		};

		GLuint indexData[] = { 0, 1 };

		GLuint vbo = 0, ibo = 0, vao = 0;

		// Create VBO
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, 2 * 2 * sizeof(GLfloat), vertextData, GL_STATIC_DRAW);

		// Create IBO
		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * sizeof(GLuint), indexData, GL_STATIC_DRAW);

		// Create VAOs
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBindVertexArray(NULL);
		VAOs.push_back(vao);
	}

	// Vertical lines
	for (int i = 0; i < cols; i++)
	{
		GLfloat vertexData[] = {
			i * tile_width, 0.f,
			i * tile_width,	rows * tile_height
		};

		GLuint indexData[] = { 0, 1 };

		GLuint vbo = 0, ibo = 0, vao = 0;

		// Create VBO
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, 2 * 2 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

		// Create IBO
		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * sizeof(GLuint), indexData, GL_STATIC_DRAW);

		// Create VAOs
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBindVertexArray(NULL);
		VAOs.push_back(vao);
	}
	// Unbind buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

std::vector<GLuint> Debug::getVAOs()
{
	return VAOs;
}

void Debug::renderMapGrid(GLuint vertextPos2DLocation)
{
	//Clear colour buffer
	glClear(GL_COLOR_BUFFER_BIT);

	// Draw vertical lines
	for (auto vao : VAOs)
	{
		
	}
	
}
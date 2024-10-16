#pragma once

#include <gl/glew.h>
#include <gl/GL.h>
#include <vector>

class Debug
{
public:
	Debug(int screenW, int screenH, float w, float h, int rows, int cols);

	void renderMapGrid(GLuint vertextPos2DLocation);

	std::vector<GLuint> getVAOs();

private:
	int screen_w, screen_h, rows, cols;
	float tile_width, tile_height;
	std::vector<GLuint> VAOs;
};


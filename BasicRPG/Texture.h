#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

class Texture
{
public:
	Texture();

	~Texture();

	// Loads image at specified path
	bool loadFromFile(SDL_Renderer* renderer, std::string path);

	//Creates image from font string
	bool loadFromRenderedText(SDL_Renderer* renderer, std::string textureText, TTF_Font* font, SDL_Color textColour);

	// Deallocates texture
	void free();

	// Set colour modulation
	void setColour(Uint8 red, Uint8 green, Uint8 blue);

	// Set blending
	void setBlendMode(SDL_BlendMode blending);

	// Set alpha modulation
	void setAlpha(Uint8 alpha);

	// Renders texture at given point
	void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* centre = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// Gets image dimensions
	int getWidth();
	int getHeight();

protected:
	// The actual hardware texture
	SDL_Texture* m_texture;

	// Image dimensions
	int m_width;
	int m_height;
};


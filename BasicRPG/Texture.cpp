#include "Texture.h"

Texture::Texture()
{
	//Initialize
	m_texture = NULL;

	m_width = 0;
	m_height = 0;
}

Texture::~Texture()
{
	//Deallocate
	free();
}

bool Texture::loadFromFile(SDL_Renderer* renderer, std::string path)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			m_width = loadedSurface->w;
			m_height = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	m_texture = newTexture;
	return m_texture != NULL;
}

bool Texture::loadFromRenderedText(SDL_Renderer* renderer, std::string textureText, TTF_Font* font, SDL_Color textColour)
{
	// Get rid preexisting texture
	free();
	
	// Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColour);
	if (textSurface == NULL)
	{
		printf("Texture loaFromRenderedText ---> Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		// Create texture from surface pixels
		m_texture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (m_texture == NULL)
		{
			printf("Texture loaFromRenderedText ---> Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			// Get image dimensions
			m_width = textSurface->w;
			m_height = textSurface->h;
		}

		// Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	// Return success
	return m_texture != NULL;
}

void Texture::free()
{
	//Free texture if it exists
	if (m_texture != NULL)
	{
		SDL_DestroyTexture(m_texture);
		m_texture = NULL;
		m_width = 0;
		m_height = 0;
	}
}

void Texture::render(SDL_Renderer* renderer ,int x, int y, SDL_Rect* clip, double angle, SDL_Point* centre, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, m_width, m_height };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopy(renderer, m_texture, clip, &renderQuad);
}

int Texture::getWidth()
{
	return m_width;
}

int Texture::getHeight()
{
	return m_height;
}
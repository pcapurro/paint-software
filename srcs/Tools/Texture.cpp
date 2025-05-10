#include "Texture.hpp"

Texture::~Texture(void)
{
	if (_texture != NULL && _texture != nullptr)
		SDL_DestroyTexture(_texture), _texture = nullptr;
}

SDL_Texture*	Texture::getTexture(void) const
{
	return (_texture);
}

int		Texture::load(const char* path, SDL_Renderer* renderer)
{
	SDL_Surface*	surface = NULL;

	surface = SDL_LoadBMP(path);
	if (surface == NULL)
		return (1);
	else
	{
		_texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		if (_texture == NULL)
			return (1);
	}

	return (0);
}
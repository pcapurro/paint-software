#ifndef TEXTURES_HPP
# define TEXTURES_HPP

# include "Global.hpp"

class Texture
{
	public:

		Texture(void) = default;

		~Texture(void)
		{
			if (_texture != NULL && _texture != nullptr)
				SDL_DestroyTexture(_texture), _texture = nullptr;
		}

		SDL_Texture*	getTexture(void) const
		{
			return (_texture);
		}

		int		load(const char* path, SDL_Renderer* renderer)
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

	private:
		SDL_Texture*	_texture = NULL;
};

struct Textures
{
	Texture	brush;
	Texture	pencil;

	Texture	spray;
	Texture	bucket;
	
	Texture	eraser;
	Texture	picker;

	Texture check;
	Texture cancel;

	Texture select;
	Texture random;
};

#endif
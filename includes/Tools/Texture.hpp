#ifndef TEXTURES_HPP
# define TEXTURES_HPP

# include "Global.hpp"

class Texture
{
	public:

		Texture(void) = default;

		~Texture(void);

		SDL_Texture*	getTexture(void) const;

		int				load(const char* path, SDL_Renderer* renderer);

	private:
		SDL_Texture*	_texture = NULL;
};

#endif
#ifndef BOX_HPP
# define BOX_HPP

# include "Global.hpp"
# include "Color.hpp"

class Box
{
	public:
		Box(const int x, const int y, const int w, const int h, \
			SDL_Texture* texture, Color color);
		~Box(void) = default;

		void	draw(SDL_Renderer* renderer);

	private:
		int 			_x;
		int 			_y;

		int 			_w;
		int 			_h;

		SDL_Texture*	_texture;
		Color			_color;
};

#endif
#include "Box.hpp"

Box::Box(const int x, const int y, const int w, const int h, \
	SDL_Texture* texture, Color color)
{
	_x = x;
	_y = y;

	_w = w;
	_h = h;

	_texture = texture;
	_color = color;
}

void	Box::draw(SDL_Renderer* renderer)
{
	SDL_Rect	obj;

	obj.x = _x;
	obj.y = _y;
	
	obj.w = _w;
	obj.h = _h;

	if (_texture != NULL && _texture != nullptr)
		SDL_RenderCopy(renderer, _texture, NULL, &obj);
	else
		SDL_RenderFillRect(renderer, &obj);
}

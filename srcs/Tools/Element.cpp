#include "Element.hpp"

Element::Element(const int x, const int y, const int w, const int h, \
	SDL_Texture* texture, Color color, const int type, const bool highlight, \
	const bool visibility)
{
	_x = x;
	_y = y;

	_w = w;
	_h = h;

	_type = type;

	_highlight = highlight;
	_visibility = visibility;

	_texture = texture;
	_color = color;
}

void	Element::draw(SDL_Renderer* renderer)
{
	SDL_Rect	obj;

	obj.x = _x;
	obj.y = _y;
	
	obj.w = _w;
	obj.h = _h;

	if (_visibility == false)
		return ;

	SDL_SetRenderDrawColor(renderer, _color.r, _color.g, _color.b, _color.a);

	if (_texture != NULL && _texture != nullptr)
		SDL_RenderCopy(renderer, _texture, NULL, &obj);
	else
		SDL_RenderFillRect(renderer, &obj);
}

bool	Element::isAbove(int x, int y) const
{
	if (_highlight == false)
		return (false);

	if (x >= _x && x <= _x + _w)
	{
		if (y >= _y && y <= _y + _h)
			return (true);
	}

	return (false);
}

#ifndef ELEMENT_HPP
# define ELEMENT_HPP

# include "Global.hpp"
# include "Color.hpp"

class Element
{
	public:
		Element(const int x, const int y, const int w, const int h, \
				SDL_Texture* texture, Color color, const int type = 0, const bool highlight = false, \
				const int highlightValue = 1, const bool visibility = true);
		~Element(void) = default;

		int				getX(void) const { return (_x); };
		int				getY(void) const { return (_y); };

		int				getW(void) const { return (_w); };
		int				getH(void) const { return (_h); };

		SDL_Texture*	getTexture(void) const { return (_texture); };
		Color			getColor(void) const { return (_color); };

		int				getType(void) const { return (_type); };
		int				getHighlight(void) const { return (_highlightValue); };

		void			setVisibility(const bool value) { _visibility = value; };
		void			setColor(Color color) { _color = color; };

		void			draw(SDL_Renderer* renderer);
		bool			isAbove(int x, int y) const;

	private:
		int 			_x;
		int 			_y;

		int 			_w;
		int 			_h;

		int				_type;

		bool			_visibility;
		bool			_highlight;
		int				_highlightValue;

		SDL_Texture*	_texture;
		Color			_color;
};

#endif
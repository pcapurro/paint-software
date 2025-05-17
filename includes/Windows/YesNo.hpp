#ifndef YESNO_HPP
# define YESNO_HPP

# include "Window.hpp"

# define YES 1
# define NO 2

class YesNo : public Window
{
	public:
		YesNo(const std::string name);
		~YesNo(void) = default;

		int		waitForEvent(void);
		void	draw(void);
		void	loadTextures(void) {};
		void	reactEvent(SDL_Event* event);
		void	generateElements(void);

		void	loadFont(void);

	private:
		TTF_Font*				_font;

		std::vector<Element>	_elements;

		int						_x;
		int						_y;

		int						_state;

};

#endif
#ifndef OK_HPP
# define OK_HPP

# include "Window.hpp"

class Ok : public Window
{
	public:
		Ok(const std::string name);
		~Ok(void) = default;

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
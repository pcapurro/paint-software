#ifndef WINDOWS_HPP
# define WINDOWS_HPP

# include "Global.hpp"

class Window
{
	public:
		Window(const std::string name, const int width, const int height);
		~Window(void);

	private:
		int				_width;
		int				_height;

		std::string		_name;

		SDL_Window*		_mainWindow;
		SDL_Renderer*	_mainRenderer;
};

#endif
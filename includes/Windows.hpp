#ifndef WINDOWS_HPP
# define WINDOWS_HPP

# include "Global.hpp"

class Window
{
	public:
		Window(const std::string name, const int width, const int height);
		virtual ~Window(void);

		virtual int	waitForEvent(void) = 0;

	private:
		int				_width;
		int				_height;

		std::string		_name;

		SDL_Window*		_mainWindow;
		SDL_Renderer*	_mainRenderer;
};

class ClassicWindow : public Window
{
	public:
		ClassicWindow(const std::string name, const int width, const int height);
		~ClassicWindow(void) = default;

		int		waitForEvent(void) { return (0); };
};

class YesNoWindow : public Window
{
	public:
		YesNoWindow(const std::string name);
		~YesNoWindow(void) = default;

		int		waitForEvent(void) { return (0); };

};

class OkCancelWindow : public Window
{
	public:
		OkCancelWindow(const std::string name);
		~OkCancelWindow(void) = default;

		int		waitForEvent(void) { return (0); };

};

#endif
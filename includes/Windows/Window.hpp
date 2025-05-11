#ifndef WINDOW_HPP
# define WINDOW_HPP

# include "Global.hpp"

# include "Tools.hpp"
# include "Color.hpp"
# include "Texture.hpp"

class Window
{
	public:
		Window(const std::string name, const int width, const int height);
		virtual ~Window(void);

		virtual int		waitForEvent(void) = 0;
		virtual void	draw(void) = 0;

		virtual void	loadTextures(void) = 0;

		virtual void	reactEvent(SDL_Event* event, const int x, const int y) = 0;
		virtual bool	isOverZone(void) const = 0;

		void			render(void);
		void			clear(void);

		SDL_Cursor*		getCursor(const int value) const;
		SDL_Renderer*	getRenderer(void) const;

		int				getWidth(void) const;
		int				getHeight(void) const;

	private:
		int					_width;
		int					_height;

		std::string			_name;

		SDL_Window*			_mainWindow;
		SDL_Renderer*		_mainRenderer;

		SDL_Cursor*			_normalCursor;
		SDL_Cursor*			_interactCursor;
};

#endif
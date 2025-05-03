#ifndef PAINT_HPP
# define PAINT_HPP

# include "Global.hpp"
# include "Windows.hpp"

class Paint
{
	public:
		Paint(void);
		~Paint(void);

		void	routine(void);

	private:
		int			_width;
		int			_height;

		Window*		_mainWindow;

		SDL_Cursor*	_normalCursor;
		SDL_Cursor*	_interactCursor;

		int			_theme;
};

#endif
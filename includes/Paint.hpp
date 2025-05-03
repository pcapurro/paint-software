#ifndef PAINT_HPP
# define PAINT_HPP

# include "Global.hpp"
# include "Windows.hpp"
# include "Textures.hpp"

class Paint
{
	public:
		Paint(void);
		~Paint(void);

		void	drawBackground(SDL_Renderer* renderer);

		void	drawToolBoxes(SDL_Renderer* renderer);
		void	drawMap(SDL_Renderer* renderer);

		void	display(void);
		void	routine(void);

	private:

		int				_width;
		int				_height;

		ClassicWindow*	_mainWindow;

		Textures		_textures;

		SDL_Cursor*		_normalCursor;
		SDL_Cursor*		_interactCursor;

		int				_theme;
};

#endif
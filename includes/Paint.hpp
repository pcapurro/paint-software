#ifndef PAINT_HPP
# define PAINT_HPP

# include "Global.hpp"
# include "Windows.hpp"
# include "Textures.hpp"
# include "Colors.hpp"

class Paint
{
	public:
		Paint(void);
		~Paint(void);

		void	loadTextures(void);
		void	initializeSDL(void);

		void	randomizeColors(void);
		void	generateColors(void);

		void	drawBackground(SDL_Renderer* renderer);
		void	drawSaveCancel(SDL_Renderer* renderer);
		void	drawTools(SDL_Renderer* renderer);
		void	drawOptions(SDL_Renderer* renderer);
		void	drawColorTools(SDL_Renderer* renderer);
		void	drawColors(SDL_Renderer* renderer);
		void	drawMap(SDL_Renderer* renderer);

		bool	isOverZone(const int x, const int y);

		void	display(void);
		void	routine(void);

		int		getRandomNumber(void);

	private:

		int					_width;
		int					_height;

		Color				_currentColor;
		std::vector<Color>	_colorsUp;
		std::vector<Color>	_colorsDown;

		ClassicWindow*		_mainWindow;

		ClassicWindow*		_saveWindow;
		ClassicWindow*		_cancelWindow;

		Textures			_textures;

		SDL_Cursor*			_normalCursor;
		SDL_Cursor*			_interactCursor;
};

#endif
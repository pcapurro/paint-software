#ifndef SOFTWARE_HPP
# define SOFTWARE_HPP

# include "Window.hpp"
# include "Icons.hpp"
# include "Box.hpp"

class Software : public Window
{
	public:

		Software(const std::string name, const int width, const int height);
		~Software(void);

		void	loadFont(void);
		void	loadTextures(void);

		bool	isOverZone(void) const;
		void	reactEvent(SDL_Event* event, const int x, const int y);

		void	drawBackground(SDL_Renderer* renderer);
		void	drawSaveCancel(SDL_Renderer* renderer);
		void	drawTools(SDL_Renderer* renderer);
		void	drawOptions(SDL_Renderer* renderer);
		void	drawColorTools(SDL_Renderer* renderer);
		void	drawColors(SDL_Renderer* renderer);
		void	drawHighlight(SDL_Renderer* renderer);
		void	drawMap(SDL_Renderer* renderer);

		void	draw(void);

		void	randomizeColors(void);
		void	generateColors(void);

		void	changeColor(Color newColor);

		int		waitForEvent(void);

	private:

		Icons				_icons;
		TTF_Font*			_font;

		std::vector<Box>	_boxes;

		int					_x;
		int					_y;

		int					_brushType;
		int					_opacity;

		bool				_highlight;

		Color				_currentColor;
		std::vector<Color>	_colorsUp;
		std::vector<Color>	_colorsDown;
};

#endif
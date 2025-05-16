#ifndef SOFTWARE_HPP
# define SOFTWARE_HPP

# include "Window.hpp"
# include "Icons.hpp"
# include "Element.hpp"

# define CHECK 1
# define CANCEL 2
# define LEFT 3
# define RIGHT 4

# define BRUSH 5
# define PENCIL 6
# define BUCKET 7
# define SPRAY 8
# define ERASER 9
# define PICKER 10
# define LINE 11
# define TEXT 12

# define BRUSH_A 13
# define BRUSH_B 14
# define BRUSH_C 15

# define COLOR 16
# define BLACK 17
# define WHITE 18

# define R 19
# define G 20
# define B 21
# define A 22

# define RANDOM 254
# define COLORS 255

class Software : public Window
{
	public:

		Software(const std::string name, const int width, const int height);
		~Software(void);

		void	loadFont(void);
		void	loadTextures(void);

		int		isOverZone(void) const;
		void	reactEvent(SDL_Event* event);

		void	generateElements(void);
		void	setOption(void);
	
		void	drawBackground(SDL_Renderer* renderer);
		void	drawHighlight(SDL_Renderer* renderer);
		void	drawMap(SDL_Renderer* renderer);
		void	drawElements(SDL_Renderer* renderer);
		void	draw(void);

		void	randomizeColors(void);
		void	changeColor(Color newColor);

		int		waitForEvent(void);

	private:

		Icons					_icons;
		TTF_Font*				_font;

		std::vector<Element>	_elements;

		int						_x;
		int						_y;

		int						_brushType;
		int						_opacity;

		bool					_highlight;

		Element*				_currentColor;
};

#endif
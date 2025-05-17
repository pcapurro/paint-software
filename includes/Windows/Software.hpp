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
# define BRUSH_D 16

# define COLOR 17
# define BLACK 18
# define WHITE 19

# define R 20
# define G 21
# define B 22
# define A 23

# define RANDOM 254
# define COLORS 255

class Software : public Window
{
	public:

		Software(const std::string name, const int width, const int height);
		~Software(void);

		int		waitForEvent(void);
		void	draw(void);
		void	loadTextures(void);
		void	reactEvent(SDL_Event* event);
		void	generateElements(void);

		void	setOption(void);
	
		void	drawHighlight(SDL_Renderer* renderer);
		void	drawMap(SDL_Renderer* renderer);
		
		void	loadFont(void);

		void	randomizeColors(void);
		void	changeColor(Color newColor);

	private:

		Icons					_icons;
		TTF_Font*				_font;

		int						_x;
		int						_y;

		int						_frameW;
		int						_frameH;

		int						_brushType;
		int						_opacity;

		bool					_highlight;

		Element*				_currentColor;

		std::vector<Element>	_elements;
};

#endif
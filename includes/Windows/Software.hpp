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

# define OP_A 17
# define OP_B 18
# define OP_C 19
# define OP_D 20

# define COLOR 21
# define BLACK 22
# define WHITE 23

# define R 24
# define G 25
# define B 26
# define A 27

# define R_VALUE 28
# define G_VALUE 29
# define B_VALUE 30
# define A_VALUE 31

# define RANDOM 254
# define COLORS 255

class Software final : public Window
{
	public:

		Software(const std::string name, const int width, const int height);
		~Software(void);

		int		waitForEvent(void);
		void	draw(void);
		void	loadImages(void);
		void	reactEvent(SDL_Event* event);
		void	generateElements(void);

		void	setBrushType(const int type);
		void	setOpacity(const int type);
	
		void	drawHighlight(SDL_Renderer* renderer);
		void	drawMap(SDL_Renderer* renderer);
		
		void	loadFont(void);

		void	refreshRGB(void);

		void	randomizeColors(void);
		void	changeColor(Color newColor);

	private:

		Icons					_icons;
		TTF_Font*				_font;

		int						_frameW;
		int						_frameH;

		int						_brushType;
		int						_opacity;

		bool					_highlight;
		bool					_colorChanged;

		Element*				_currentColor;
		std::vector<Element>	_elements;
};

#endif
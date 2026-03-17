#ifndef PAINTSOFTWARE_HPP
# define PAINTSOFTWARE_HPP

# include "Window.hpp"

# include "Image.hpp"
# include "Shape.hpp"

# include "PaintFrame.hpp"

class PaintSoftware : public Window
{
    private:
        PaintFrame			_frame;

		vector<Image>		_mainButtons;
		vector<Image>		_tools;
		vector<Image>		_brushCursors;
		vector<Shape>		_brushOptions;
		vector<Shape>		_opacityCursors;
		optional<Shape>		_opacityOption;

		vector<Shape>		_colorsOptions;
		vector<Shape>		_randomColors;

    public:
		PaintSoftware(const string& name, const int width, const int height, \
			const int frameWidth, const int frameHeight);
		~PaintSoftware(void) = default;

		void				initMainButtons(void);
		void				initTools(void);
		void				initBrushOptions(void);
		void				initOpacityOption(void);

		void				initColorsOptions(void);
		void				initRandomColors(void);

		int         		routine(void);
		int         		waitForEvent(void);

		void        		render(void);
		int         		reactEvent(SDL_Event* event, const int x = 0, const int y = 0);
};

#endif

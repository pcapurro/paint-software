#ifndef PAINTSOFTWARE_HPP
# define PAINTSOFTWARE_HPP

# include "Window.hpp"

# include "ImageButton.hpp"
# include "Shape.hpp"

# include "PaintFrame.hpp"

class PaintSoftware : public Window
{
    private:
        optional<PaintFrame>				_paintFrame;

		vector<unique_ptr<ImageButton>>		_mainButtons;
		vector<unique_ptr<ImageButton>>		_tools;

		vector<unique_ptr<ImageButton>>		_brushCursors;
		vector<Shape>						_opacityCursors;

		vector<Shape>						_colorsOptions;
		vector<Shape>						_randomColors;

		vector<Shape>						_decoyShapes;

		void								initFrame(const int frameWidth, const int frameHeight);

		void								initMainButtons(SDL_Renderer* renderer);
		void								initTools(SDL_Renderer* renderer);

		void								initBrushOptions(SDL_Renderer* renderer);
		void								initOpacityOption(SDL_Renderer* renderer);

		void								initColorsOptions(SDL_Renderer* renderer);
		void								initRandomColors(SDL_Renderer* renderer);

    public:
		PaintSoftware(const string& name, const int width, const int height, \
			const int frameWidth, const int frameHeight);
		~PaintSoftware(void) = default;

		int         			routine(void);
		int         			waitForEvent(void);

		void        			render(void);
		int         			reactEvent(SDL_Event* event, const int x = 0, const int y = 0);
};

#endif

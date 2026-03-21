#ifndef PAINTSOFTWARE_HPP
# define PAINTSOFTWARE_HPP

# include "Window.hpp"

# include "MainBox.hpp"
# include "ToolBox.hpp"
# include "SliderBox.hpp"

# include "PaintFrame.hpp"

class PaintSoftware : public Window
{
    private:
        optional<PaintFrame>	_paintFrame;

		optional<MainBox>		_mainBox;
		optional<ToolBox>		_toolBox;

		optional<Shape>			_leftEndLine;

		optional<SliderBox>		_brushSlider;
		optional<SliderBox>		_opacitySlider;

		int						_selectedTool = BRUSH;
		Color					_selectedColor;

		int						_cursor = SDL_SYSTEM_CURSOR_ARROW;

		void					initFrame(const int frameWidth, const int frameHeight);

		void					initMainButtons(SDL_Renderer* renderer);
		void					initTools(SDL_Renderer* renderer);

		void					initBrushTools(SDL_Renderer* renderer);

    public:
		PaintSoftware(const string& name, const int width, const int height, \
			const int frameWidth, const int frameHeight);
		~PaintSoftware(void) = default;

		void    				execMain(void);
		void    				execTool(void);
		void					exec(void);

		int         			waitForEvent(void);

		int         			routine(void);

		void        			render(void);

		void					reactMouseMotion(const int x, const int y);
		void					reactMouseButtonDown(const int x, const int y);
		void					reactMouseButtonUp(const int x, const int y);

		int						reactEvent(SDL_Event* event, const int x = 0, const int y = 0);
};

#endif

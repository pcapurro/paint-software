#ifndef PAINTSOFTWARE_HPP
# define PAINTSOFTWARE_HPP

# include "Window.hpp"

# include "BrushOptions.hpp"
# include "MainBox.hpp"
# include "ToolBox.hpp"

# include "PaintFrame.hpp"

class PaintSoftware : public Window
{
    private:
        optional<PaintFrame>				_paintFrame;

		optional<MainBox>					_mainBox;
		optional<ToolBox>					_toolBox;
		optional<BrushOptions>				_brushOptions;

		optional<Shape>						_leftEndLine;

		int									_cursor = SDL_SYSTEM_CURSOR_ARROW;

		void								initFrame(const int frameWidth, const int frameHeight);

		void								initMainButtons(SDL_Renderer* renderer);
		void								initTools(SDL_Renderer* renderer);

		void								initBrushOptions(SDL_Renderer* renderer);

    public:
		PaintSoftware(const string& name, const int width, const int height, \
			const int frameWidth, const int frameHeight);
		~PaintSoftware(void) = default;

		int         			routine(void);
		int         			waitForEvent(void);

		void        			render(void);

		void					reactMouseMotion(const int x, const int y);
		void					reactMouseButtonDown(const int x, const int y);
		void					reactMouseButtonUp(const int x, const int y);

		int         			reactEvent(SDL_Event* event, const int x = 0, const int y = 0);
};

#endif

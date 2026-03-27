#ifndef PAINTSOFTWARE_HPP
# define PAINTSOFTWARE_HPP

# include "Window.hpp"

# include "MainBox.hpp"
# include "ToolBox.hpp"
# include "ColorButton.hpp"
# include "SliderBox.hpp"

# include "PaintFrame.hpp"

# include "PathSelection.hpp"
# include "ColorSelection.hpp"

class PaintSoftware : public Window
{
    private:
        optional<PaintFrame>	_paintFrame;

		optional<MainBox>		_mainBox;
		optional<ToolBox>		_toolBox;

		optional<SliderBox>		_brushSlider;
		optional<SliderBox>		_opacitySlider;

		optional<Text>			_colorText;
		optional<ColorButton>	_colorButton;
		optional<ColorButton>	_blackButton;
		optional<ColorButton>	_whiteButton;

		optional<Shape>			_endLine;

		int						_selectedTool = BRUSH;
		Color					_selectedColor;

		int						_brushSize;

		int						_cursor = SDL_SYSTEM_CURSOR_ARROW;

		void					initFrame(const int frameWidth, const int frameHeight);

		void					initMainButtons(SDL_Renderer* renderer);
		void					initTools(SDL_Renderer* renderer);

		void					initBrushTools(SDL_Renderer* renderer);

		void					initColors(SDL_Renderer* renderer);

		Color					generateRandomColor(void) const noexcept;

    public:
		PaintSoftware(const string& name, const int width, const int height, \
			const int frameWidth, const int frameHeight);
		~PaintSoftware(void) = default;

		void    				updateMain(void);
		void    				updateTool(void);
		void					updateBrush(void);
		void					updateOpacityFromSlider(void);
		void					updateOpacityFromValue(const uint8_t opacity);
		void    				updateColor(const Color& newColor);
		void    				updateColorText(void);

		void					update(void);

		void					execSave(void);
		void					execCancel(void);

		void					execBack(void);
		void					execForward(void);

		void					execColorSwitch(const Color& newColor);

		void        			render(void);

		void					reactMouseMotion(const int x, const int y);
		void					reactMouseButtonDown(const int x, const int y);
		void					reactMouseButtonUp(const int x, const int y);

		void					reactKeyButtonDown(const int key);

		int						reactEvent(SDL_Event* event);
};

#endif

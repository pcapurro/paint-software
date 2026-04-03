#ifndef PAINTVIEW_HPP
# define PAINTVIEW_HPP

# include "Window.hpp"

# include "MainBox.hpp"
# include "ToolBox.hpp"
# include "ColorButton.hpp"
# include "SliderBox.hpp"

# include "PaintFrame.hpp"

# include "PathSelection.hpp"
# include "ColorSelection.hpp"

class PaintView : public Window
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

		int						_selectedTool = ToolBox::Brush;
		Color					_selectedColor;

		int						_brushSize = BrushDefaultSize;

		int						_cursor = SDL_SYSTEM_CURSOR_ARROW;
		optional<Shape>			_brushScope;
		optional<Image>			_customCursor;

		static constexpr int    Border = 2;

		static constexpr int	ButtonWidth = 65;
		static constexpr int	ButtonHeight = 65;

		static constexpr int	CenterSpaceWidth = 20;
		static constexpr int	CenterSpaceHeight = 20;

		static constexpr int	LeftPanelsWidth = 150;

		static constexpr int	MainHeight = 130;
		static constexpr int	ToolboxHeight = 260;

		static constexpr int	SlideBoxHeight = 45;

		static constexpr int	MainColorHeight = 45;
		static constexpr int	SideColorHeight = 36;

		static constexpr int	BorderLen = 2;

		static constexpr int	WidthLimit = 20;
		static constexpr int	HeightUpLimit = 30;
		static constexpr int	HeightDownLimit = 30;

		static constexpr int	Save = 1;
		static constexpr int	Cancel = 2;
		static constexpr int	Back = 3;
		static constexpr int	Forward = 4;

		static constexpr int	BrushMinimumSize = 1;
		static constexpr int	BrushMaximumSize = 50;
		static constexpr int	BrushDefaultSize = 21;

		static constexpr int	OpacityMinimum = 1;
		static constexpr int	OpacityMaximum = 255;

		static constexpr int	DefaultOpacity = 255;
		
		static constexpr int	LineHeight = 7;

		static constexpr int	DefaultCursorWidth = 45;
		static constexpr int	DefaultCursorHeight = 45;

		void					initBrushScope(void);
		void					initCustomCursor(SDL_Renderer* renderer);

		void					initFrame(const int frameWidth, const int frameHeight);

		void					initMainButtons(SDL_Renderer* renderer);
		void					initTools(SDL_Renderer* renderer);

		void					initBrushTools(SDL_Renderer* renderer);

		void					initColors(SDL_Renderer* renderer);

		Color					generateRandomColor(void) const noexcept;

    public:
		PaintView(const string& name, const int width, const int height, \
			const int frameWidth, const int frameHeight);
		~PaintView(void) = default;

		void    				updateMain(void);
		void    				updateTool(void);
		void					updateBrush(void);
		void					updateOpacityFromSlider(void);
		void					updateOpacityFromValue(const uint8_t opacity);
		void    				updateColor(const Color& newColor);
		void    				updateColorText(void);
		void    				updateCursorImage(void);
		void    				updateBrushScope(void);
		void    				updateBrushScopePosition(void);
		void    				updateCursorPosition(void);
		void					updateMouse(void);

		void					update(void);

		void					execSave(void);
		void					execCancel(void);

		void					execBack(void);
		void					execForward(void);

		void					execColorSwitch(const Color& newColor);

		void					render(void);

		void					reactMouseMotion(const int x, const int y);
		void					reactMouseButtonDown(const int x, const int y);
		int						reactMouseButtonUp(const int x, const int y);

		void					reactKeyButtonDown(const int key);

		int						reactEvent(SDL_Event* event);

		static constexpr int	LeftWidth = 190;
		static constexpr int	RightWidth = 30;

		static constexpr int	UpHeight = 30;
		static constexpr int	DownHeight = 30;

		static constexpr int	MinPaintWidth = 50;
		static constexpr int	MinPaintHeight = 50;
		static constexpr int	MaxPaintWidth = 1280;
		static constexpr int	MaxPaintHeight = 720;

		static constexpr int	MinimumWidth = MaxPaintWidth;
		static constexpr int	MinimumHeight = MaxPaintHeight;

		static constexpr int	ColorSwitch = 256;
};

#endif

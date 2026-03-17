#include "PaintSoftware.hpp"

PaintSoftware::PaintSoftware(const string& name, const int width, const int height, \
    const int frameWidth, const int frameHeight) : \
		Window(name, width, height), \
		_frame(frameWidth, frameHeight)
{
	setBackgroundColor(DEF_BACK_COLOR);

	initMainButtons();
	initTools();
	initBrushOptions();
	initOpacityOption();

	initColorsOptions();
	initRandomColors();
}

void	PaintSoftware::initMainButtons(void)
{
	_mainButtons.reserve(4);

	// ...
}

void	PaintSoftware::initTools(void)
{
	_tools.reserve(8);

	// ...
}

void	PaintSoftware::initBrushOptions(void)
{
	_brushCursors.reserve(4);
	_brushOptions.reserve(4);

	// ...
}

void	PaintSoftware::initOpacityOption(void)
{
	_opacityCursors.reserve(5);
	// _opacityOption.emplace()

	// ...
}

void	PaintSoftware::initColorsOptions(void)
{
	_colorsOptions.reserve(3);

	// ...
}

void	PaintSoftware::initRandomColors(void)
{
	// _randomColors.reserve(42);
	// ...
}

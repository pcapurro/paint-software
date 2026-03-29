#include "PaintView.hpp"

PaintView::PaintView(const string& name, const int width, const int height, \
    const int frameWidth, const int frameHeight) : \
		Window(name, width, height)
{
	setBackgroundColor(Color::Black);
	setWriteColor(Color::White);

	std::srand(std::time(nullptr));

	_selectedColor = generateRandomColor();

	SDL_Renderer*	renderer = getRenderer();

	initFrame(frameWidth, frameHeight);

	initMainButtons(renderer);
	initTools(renderer);

	initBrushTools(renderer);

	initColors(renderer);

	if (_colorButton->getY() + _colorButton->getHeight() < \
		(_paintFrame->getY() + _paintFrame->getHeight()) - (LineHeight / 2) - CenterSpaceHeight)
	{
		_endLine.emplace(WidthLimit, _paintFrame->getY() + _paintFrame->getHeight() - (LineHeight / 2), \
			LeftPanelsWidth, (LineHeight), getWriteColor());
	}
}

void	PaintView::initFrame(const int frameWidth, const int frameHeight)
{
	int		frameSpaceWidth = getWidth() - LeftWidth - RightWidth;
	int		frameSpaceHeight = getHeight() - UpHeight - DownHeight;

	int		frameX = LeftWidth + ((frameSpaceWidth / 2) - (frameWidth / 2));
	int		frameY = UpHeight + ((frameSpaceHeight / 2) - (frameHeight / 2));

	Color	backColor = getWriteColor();

	_paintFrame.emplace(frameX, frameY, frameWidth, frameHeight, backColor);
}

void	PaintView::initMainButtons(SDL_Renderer* renderer)
{
	_mainBox.emplace(WidthLimit, HeightUpLimit, LeftPanelsWidth, MainHeight, \
		getBackgroundColor(), getWriteColor(), renderer);
}

void	PaintView::initTools(SDL_Renderer* renderer)
{
	_toolBox.emplace(WidthLimit, _mainBox->getY() + _mainBox->getHeight() + CenterSpaceHeight, \
		LeftPanelsWidth, ToolboxHeight, getBackgroundColor(), getWriteColor(), renderer);
}

void	PaintView::initBrushTools(SDL_Renderer* renderer)
{
	string	fontPath = "materials/font/OpenSans.ttf";

	Color	backColor = getBackgroundColor();
	Color	writeColor = getWriteColor();

	_brushSlider.emplace(WidthLimit, _toolBox->getY() + _toolBox->getHeight() + CenterSpaceHeight, \
		LeftPanelsWidth, SlideBoxHeight, fontPath, BrushMinimumSize, BrushMaximumSize, BrushDefaultSize, \
		"Brush size: ", 11, true, 2, backColor, writeColor, writeColor, writeColor, renderer);

	_opacitySlider.emplace(WidthLimit, _brushSlider->getY() + _brushSlider->getHeight() + Border, \
		LeftPanelsWidth, SlideBoxHeight, fontPath, OpacityMinimum, OpacityMaximum, DefaultOpacity, \
		"Opacity: ", 11, true, 2, backColor, writeColor, writeColor, writeColor, renderer);
}

void	PaintView::initColors(SDL_Renderer* renderer)
{
	Color	black = Color::Black;
	Color	white = Color::White;

	string	fontPath = "materials/font/OpenSans.ttf";
	Color	writeColor = getWriteColor();

	string	colorText = std::to_string(_selectedColor.r) + ", " + std::to_string(_selectedColor.g) \
		+ ", " + std::to_string(_selectedColor.b) + ", " + std::to_string(_selectedColor.a);

	_colorText.emplace(0, _opacitySlider->getY() + _opacitySlider->getHeight() \
		+ CenterSpaceHeight, colorText, 12, fontPath, getWriteColor(), LeftPanelsWidth, \
		false, renderer);

	_colorText->setX((LeftWidth / 2) - (_colorText->getWidth() / 2), renderer);

	_colorButton.emplace(WidthLimit, _colorText->getY() + _colorText->getHeight() \
		+ (CenterSpaceHeight / 2), (ButtonWidth * 2 + CenterSpaceWidth), MainColorHeight, \
		_selectedColor, getWriteColor(), renderer);

	_blackButton.emplace(WidthLimit, _colorButton->getY() + _colorButton->getHeight() \
		+ (CenterSpaceHeight / 2), ButtonWidth, SideColorHeight, black, getWriteColor(), renderer);

	_whiteButton.emplace(WidthLimit + _blackButton->getWidth() + CenterSpaceWidth, \
		_colorButton->getY() + _colorButton->getHeight() + (CenterSpaceHeight / 2), \
		ButtonWidth, SideColorHeight, white, getWriteColor(), renderer);
}

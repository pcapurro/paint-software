#include "ColorSelection.hpp"

void	ColorSelection::addLogo(const int cursorX, const int cursorY, const string& logoPath, \
	const int logoWidth, const int logoHeight, const bool centered)
{
	Properties		logoProperties;
	SDL_Renderer*	renderer = getRenderer();

	if (!centered)
		logoProperties.x = cursorX;

	logoProperties.y = cursorY;

	logoProperties.width = logoWidth;
	logoProperties.height = logoHeight;

	auto	image = std::make_unique<Image>(logoProperties.x, logoProperties.y, \
		logoProperties.width, logoProperties.height, logoPath.c_str(), renderer);

	if (centered)
		image->setX(getWidth() / 2 - (image->getWidth() / 2), renderer);

	_elements.emplace_back(std::move(image));
}

void	ColorSelection::addTitleText(const int cursorX, const int cursorY, const string& text, \
	const string& fontPath, const int maxWidth)
{
	int		titleSize = getHeight() * TITLE_RATIO;

	unique_ptr<Text>	textElement = std::make_unique<Text>(cursorX, cursorY, \
		text.c_str(), titleSize, fontPath, getWriteColor(), maxWidth, true, getRenderer());

	_elements.emplace_back(std::move(textElement));
}

void	ColorSelection::addTitleLimit(const int cursorX, const int cursorY, const int width)
{
	auto	shapeElement = std::make_unique<Shape>(cursorX, cursorY, width, \
		LIMIT_HEIGHT, getWriteColor());

	_elements.emplace_back(std::move(shapeElement));
}

void	ColorSelection::addText(const int cursorX, const int cursorY, const string& text, \
	const string& fontPath, const int maxWidth)
{
	int		textSize = getHeight() * TEXT_RATIO;

	auto	textElement = std::make_unique<Text>(cursorX, cursorY, text.c_str(), \
		textSize, fontPath, getWriteColor(), maxWidth, true, getRenderer());

	_elements.emplace_back(std::move(textElement));
}

void	ColorSelection::addColorView(void)
{
	int				viewHeight = (_leftDownField->getY() + \
		_leftDownField->getHeight()) - _leftUpField->getY();

	SDL_Renderer*	renderer = getRenderer();

	_colorView.emplace(0, _leftUpField->getY(), COLOR_VIEW_W, viewHeight, \
		getBackgroundColor(), getWriteColor(), renderer);

	_colorView->setX(_rightUpField->getX() + \
		_rightUpField->getWidth() + CENTER_SPACE_W, renderer);
}


void	ColorSelection::addButton(const string& fontPath)
{
    int				textSize = getHeight() * TEXT_RATIO;
	int				limitX = getWidth() * LIMIT_RATIO;
	int				limitY = getHeight() * LIMIT_RATIO;

	int				globalWidth = ((textSize * 5) / 10) * 10;
	int				globalHeight = ((textSize * 2) / 10) * 10;

	SDL_Renderer*	renderer = getRenderer();

	_okButton = std::make_unique<TextButton>(0, 0, globalWidth, globalHeight, \
		getBackgroundColor(), "OK", textSize, getWriteColor(), fontPath, renderer);

	_okButton->setX(getWidth() - limitX - _okButton->getWidth(), renderer);
	_okButton->setY(getHeight() - limitY - _okButton->getHeight(), renderer);

	_okButton->setSettings(false, NONE, true, SDL_SYSTEM_CURSOR_HAND, true, true);
}

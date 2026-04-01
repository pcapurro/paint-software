#include "ColorSelection.hpp"

void	ColorSelection::addLeftFieldsTitles(const string& fontPath)
{
    int				textSize = getHeight() * Render::TextRatio;
	int				limitX = getWidth() * Render::LimitRatio;
	int				limitY = getHeight() * Render::LimitRatio;

	SDL_Renderer*	renderer = getRenderer();

	Color			blue = Color::Blue;
	Color			red = Color::Red;

	auto 	downLeftText = std::make_unique<Text>(limitX, 0, "B", textSize, \
		fontPath, blue, 0, false, renderer);

	downLeftText->setY(getHeight() - (limitY * 3) - downLeftText->getHeight());

	auto 	upLeftText = std::make_unique<Text>(limitX, 0, "R", textSize, \
		fontPath, red, 0, false, renderer);

	upLeftText->setY(downLeftText->getY() - (limitY * 3) - upLeftText->getHeight());

	_elements.emplace_back(std::move(upLeftText));
	_elements.emplace_back(std::move(downLeftText));
}

void	ColorSelection::addLeftFields(const string& fontPath, const int maxText)
{
    int				textSize = getHeight() * Render::TextRatio;
	int				limitX = getWidth() * Render::LimitRatio;

	int				globalWidth = ((textSize * 5) / 10) * 10;
	int				globalHeight = ((textSize * 2) / 10) * 10;

	Text*			upText = dynamic_cast<Text*>(_elements[_elements.size() - 2].get());
	Text*			downText = dynamic_cast<Text*>(_elements.back().get());

	int				globalX = 0;

	if (downText->getX() + downText->getWidth() > upText->getX() + upText->getWidth())
		globalX = downText->getX() + downText->getWidth();
	else
		globalX = upText->getX() + upText->getWidth();

	SDL_Renderer*	renderer = getRenderer();

	_leftDownField = std::make_unique<ValueField>(globalX + limitX, 0, \
		globalWidth, globalHeight, getBackgroundColor(), getWriteColor(), \
		fontPath, getWriteColor(), maxText, 0, 255);

	_leftDownField->setY(downText->getY(), renderer);	
	_leftDownField->setSettings(true, Render::HighlightSelect, true, SDL_SYSTEM_CURSOR_IBEAM, false, false);

	Color	blue = Color::Blue;
	blue.a = Render::HiglihtOpacity;

	_leftDownField->setSelectColor(blue);

	_leftUpField = std::make_unique<ValueField>(globalX + limitX, 0, globalWidth, globalHeight, \
		getBackgroundColor(), getWriteColor(), fontPath, getWriteColor(), maxText, 0, 255);

	_leftUpField->setY(upText->getY(), renderer);
	_leftUpField->setSettings(true, Render::HighlightSelect, true, SDL_SYSTEM_CURSOR_IBEAM, false, false);

	_leftUpField->setSelectColor(blue);

	Color	backColor = getBackgroundColor();

	_leftUpField->add(std::to_string(backColor.r), renderer);
	_leftDownField->add(std::to_string(backColor.b), renderer);
}

void	ColorSelection::addLeftFieldsErrors(const string& fontPath)
{
    int				textSize = getHeight() * Render::TextRatio;
	int				limitX = getWidth() * Render::LimitRatio;

	SDL_Renderer*	renderer = getRenderer();

	_leftDownError = std::make_unique<Text>(0, 0, "Default error", textSize, \
		fontPath, getWriteColor(), 0, false, renderer);

	Text*	downText = dynamic_cast<Text*>(_elements.back().get());

	_leftDownError->setX(downText->getX() + downText->getWidth() + (limitX / 2));
	_leftDownError->setY(_leftDownField->getY() + _leftDownField->getHeight());

	_leftDownError->setColor(Color::Red);
	_leftDownError->setVisibility(false);

	Text*	upText = dynamic_cast<Text*>(_elements[_elements.size() - 2].get());
	_leftUpError = std::make_unique<Text>(0, 0, "Default error", textSize, \
		fontPath, getWriteColor(), 0, false, renderer);

	_leftUpError->setX(upText->getX() + upText->getWidth() + (limitX / 2));
	_leftUpError->setY((_leftUpField->getY() + _leftUpField->getHeight()));

	_leftUpError->setColor(Color::Red);
	_leftUpError->setVisibility(false);
}

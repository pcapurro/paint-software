#include "ColorSelection.hpp"

void	ColorSelection::addRightFieldsTitles(const string& fontPath)
{
    int				textSize = getHeight() * Render::TextRatio;

    int             leftUpFieldUnitX = _leftUpField->getX() \
						+ _leftUpField->getWidth() + (CenterSpaceWidth / 2);
    int             leftDownFieldUnitX = _leftDownField->getX() \
						+ _leftDownField->getWidth() + (CenterSpaceWidth / 2);

    int             limitX = leftUpFieldUnitX > leftDownFieldUnitX \
                        ? leftUpFieldUnitX : leftDownFieldUnitX;

	int				limitY = getHeight() * Render::LimitRatio;

	SDL_Renderer*	renderer = getRenderer();

	Color			green = Color::Green;

	auto 	downRightText = std::make_unique<Text>(limitX, 0, "A", textSize, \
		fontPath, getWriteColor(), 0, false, renderer);

	downRightText->setY(getHeight() - (limitY * 3) - downRightText->getHeight());

	auto 	upRightText = std::make_unique<Text>(limitX, 0, "G", textSize, \
		fontPath, green, 0, false, renderer);

	upRightText->setY(downRightText->getY() - (limitY * 3) - upRightText->getHeight());

	_elements.emplace_back(std::move(upRightText));
	_elements.emplace_back(std::move(downRightText));
}

void	ColorSelection::addRightFields(const string& fontPath, const int maxText)
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

	_rightDownField = std::make_unique<ValueField>(globalX + limitX, 0, \
		globalWidth, globalHeight, getBackgroundColor(), getWriteColor(), \
		fontPath, getWriteColor(), maxText, 1, 255);

	_rightDownField->setY(downText->getY(), renderer);	
	_rightDownField->setSettings(true, Render::HighlightSelect, true, SDL_SYSTEM_CURSOR_IBEAM, false, false);

	_rightDownField->setSelectColor(Color::Blue.toNewOpacity(Render::HiglihtOpacity));

	_rightUpField = std::make_unique<ValueField>(globalX + limitX, 0, globalWidth, globalHeight, \
		getBackgroundColor(), getWriteColor(), fontPath, getWriteColor(), maxText, 0, 255);

	_rightUpField->setY(upText->getY(), renderer);
	_rightUpField->setSettings(true, Render::HighlightSelect, true, SDL_SYSTEM_CURSOR_IBEAM, false, false);

	_rightUpField->setSelectColor(Color::Blue.toNewOpacity(Render::HiglihtOpacity));

	Color	backColor = getBackgroundColor();

	_rightUpField->add(std::to_string(backColor.b), renderer);
	_rightDownField->add(std::to_string(backColor.a), renderer);
}

void	ColorSelection::addRightFieldsErrors(const string& fontPath)
{
    int				textSize = getHeight() * Render::TextRatio;
	int				limitX = getWidth() * Render::LimitRatio;

	SDL_Renderer*	renderer = getRenderer();

	_rightDownError = std::make_unique<Text>(0, 0, "Default error", textSize, \
		fontPath, getWriteColor(), 0, false, renderer);

	Text*	downText = dynamic_cast<Text*>(_elements.back().get());

	_rightDownError->setX(downText->getX() + downText->getWidth() + (limitX / 2));
	_rightDownError->setY(_rightDownField->getY() + _rightDownField->getHeight());

	_rightDownError->setColor(Color::Red);
	_rightDownError->setVisibility(false);

	Text*	upText = dynamic_cast<Text*>(_elements[_elements.size() - 2].get());
	_rightUpError = std::make_unique<Text>(0, 0, "Default error", textSize, \
		fontPath, getWriteColor(), 0, false, renderer);

	_rightUpError->setX(upText->getX() + upText->getWidth() + (limitX / 2));
	_rightUpError->setY(_rightUpField->getY() + _rightUpField->getHeight());

	_rightUpError->setColor(Color::Red);
	_rightUpError->setVisibility(false);
}

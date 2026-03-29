#include "ColorSelection.hpp"

ColorSelection::ColorSelection(const string& name, const string& fontPath, \
	const int width, const int height, const int displayMode, const string& titleText, \
	const bool titleLimit, const string& text) : \
		Window(name, width, height), \
		_fontPath(fontPath)
{
	int		limitX = width * Render::LimitRatio;
	int		limitY = height * Render::LimitRatio;

	int		cursorX = limitX;
	int		cursorY = limitY;

	int		maxWidth = width - (limitX * 2);

	if (displayMode == Window::DarkMode)
		setWriteColor(Color::White), setBackgroundColor(Color::Black);
	else
		setWriteColor(Color::Black), setBackgroundColor(Color::White);

	_elements.reserve(8);
	_finalValues.reserve(4);

	if (titleText.size() > 0)
	{
		if (_elements.size() > 0)
			cursorX += _elements.back()->getWidth() + limitX;

		maxWidth = width - cursorX - limitX;

		addTitleText(cursorX, cursorY, titleText, fontPath, maxWidth);

		cursorY += _elements.back()->getHeight() + limitY;
	}

	if (titleLimit)
	{
		addTitleLimit(cursorX, cursorY, maxWidth);
		cursorY += _elements.back()->getHeight() + limitY;
	}
	
	cursorX = limitX;

	maxWidth = width - (limitX * 2);

	addText(cursorX, cursorY, text, fontPath, maxWidth);

	addLeftFieldsTitles(fontPath);
	addLeftFields(fontPath, 3);
	addLeftFieldsErrors(fontPath);

	addRightFieldsTitles(fontPath);
	addRightFields(fontPath, 3);
	addRightFieldsErrors(fontPath);

	addColorView();
	addButton(fontPath);
}

#include "ColorSelection.hpp"

void	ColorSelection::reactError(void)
{
	vector<Text*>	errorsPtr = { _leftDownError.get(), _leftUpError.get(), \
		_rightUpError.get(), _rightDownError.get() };
	vector<string>	errorsText = { _leftDownField->getLastError(), _leftUpField->getLastError(), \
		_rightUpField->getLastError(), _rightDownField->getLastError() };

	int		limitX = getWidth() * LIMIT_RATIO;
	int		maxWidth = getWidth() - (limitX * 2);

	_error = false;

	for (size_t i = 0; i < errorsPtr.size(); i++)
	{
		if (!errorsPtr[i])
			continue;

		if (errorsText[i].size() > 0)
		{
			errorsPtr[i]->update(errorsText[i], maxWidth, false, getRenderer());
			errorsPtr[i]->setVisibility(true);

			_error = true;
		}
		else
			errorsPtr[i]->setVisibility(false);
	}
}

void	ColorSelection::reactMouseMotion(const int x, const int y)
{
	bool				isAbove = false;
	SDL_Renderer*		renderer = getRenderer();
	vector<Element*>	buttons = { _okButton.get(), _leftUpField.get(), \
		_leftDownField.get(), _rightUpField.get(), _rightDownField.get() };

	for (auto& button : buttons)
	{
		if (button->isAbove(x, y))
		{
			button->onMouseHover(x, y, renderer);
			SDL_SetCursor(getCursor(button->getHoverCursor()));

			isAbove = true;
		}
		else
			button->onMouseHoverOutside(renderer);
	}

    if (!isAbove)
        SDL_SetCursor(getCursor(SDL_SYSTEM_CURSOR_ARROW));
}

int		ColorSelection::reactMouseButtonUp(const int x, const int y)
{
	SDL_Renderer*		renderer = getRenderer();
	vector<Element*>	buttons = { _okButton.get(), _leftUpField.get(), \
		_leftDownField.get(), _rightUpField.get(), _rightDownField.get() };

	for (auto& button : buttons)
	{
		if (button->isAbove(x, y))
		{
			button->onMouseUp(x, y, renderer);

			ValueField*	textField = dynamic_cast \
				<ValueField*>(button);

			if (!textField)
				return RETURN;
		}
		else
			button->onMouseUpOutside(renderer);
	}

	return OK;
}

void	ColorSelection::reactMouseButtonDown(const int x, const int y, \
	const int clicks)
{
	SDL_Renderer*		renderer = getRenderer();
	vector<Element*>	buttons = { _okButton.get(), _leftUpField.get(), \
		_leftDownField.get(), _rightUpField.get(), _rightDownField.get() };

	for (auto& button : buttons)
	{
		if (button->isAbove(x, y))
		{
			if (clicks > 1)
				button->onMouseDownDouble(x, y, renderer);
			else
				button->onMouseDown(x, y, renderer);
		}
		else
			button->onMouseDownOutside(renderer);
	}
}

int		ColorSelection::reactKeyButtonDown(const int key)
{
	vector<Element*>	buttons = { _leftUpField.get(), _rightUpField.get(), \
		_leftDownField.get(), _rightDownField.get(), _okButton.get() };

	SDL_Renderer*		renderer = getRenderer();

	for (const auto& button : buttons)
		button->onButtonDown(key, renderer);

	if (key == SDLK_BACKSPACE || key == SDLK_DELETE)
		reactColorUpdate();

	if (key == SDLK_TAB)
	{
		buttons[_tabCursor]->setClick(false);
		buttons[_tabCursor]->setSelected(false);
		buttons[_tabCursor]->setHover(false);

		if (_tabCursor < buttons.size() - 1)
			_tabCursor++;
		else
			_tabCursor = 0;

		buttons[_tabCursor]->setHover(true);
	}
	else if (key == SDLK_RETURN || key == SDLK_KP_ENTER)
	{
		buttons[_tabCursor]->onMouseDown();

		TextButton*	textButton = dynamic_cast \
			<TextButton*>(buttons[_tabCursor]);

		if (textButton)
			return RETURN;
	}
	
	reactError();

	return OK;
}

void	ColorSelection::reactCharactersDown(const char* text)
{
	SDL_Renderer*		renderer = getRenderer();
	bool				refresh = false;

	if (_leftUpField->isClicked())
		_leftUpField->add(text, renderer), refresh = true;

	else if (_leftDownField->isClicked())
		_leftDownField->add(text, renderer), refresh = true;

	else if (_rightUpField->isClicked())
		_rightUpField->add(text, renderer), refresh = true;

	else if (_rightDownField->isClicked())
		_rightDownField->add(text, renderer), refresh = true;

	if (refresh)
		reactColorUpdate();

	reactError();
}

void	ColorSelection::reactColorUpdate(void)
{
	Color	newColor;

	newColor.r = _leftUpField->getValue();
	newColor.g = _rightUpField->getValue();
	newColor.b = _leftDownField->getValue();

	newColor.a = 255;

	_colorView->setMainColor(newColor);
}

int		ColorSelection::reactEvent(SDL_Event* event, const int x, const int y)
{
	int		value = OK;

	if (event->type == SDL_MOUSEMOTION)
		reactMouseMotion(x, y);

	else if (event->type == SDL_MOUSEBUTTONDOWN \
		&& event->button.button == SDL_BUTTON_LEFT)
		reactMouseButtonDown(x, y, event->button.clicks);

	else if (event->type == SDL_MOUSEBUTTONUP \
		&& event->button.button == SDL_BUTTON_LEFT)
		value = reactMouseButtonUp(x, y);

	else if (event->type == SDL_KEYDOWN)
		value = reactKeyButtonDown(event->key.keysym.sym);

	else if (event->type == SDL_TEXTINPUT)
		reactCharactersDown(event->text.text);

	refreshDisplay();

	return value;
}

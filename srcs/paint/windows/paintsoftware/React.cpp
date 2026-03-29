#include "PaintView.hpp"

void    PaintView::reactMouseMotion(const int x, const int y)
{
    bool                isHover = false;
    SDL_Renderer*       renderer = getRenderer();

    vector<Element*>    elements = {&_paintFrame.value(), &_mainBox.value(), \
        &_toolBox.value(), &_brushSlider.value(), &_opacitySlider.value(), \
        &_colorButton.value(), &_blackButton.value(), &_whiteButton.value()};

    for (auto& element : elements)
    {
        if (element->isAbove(x, y))
        {
            element->onMouseHover(x, y, renderer);

            if (element->isHover())
            {
                _cursor = element->getHoverCursor();

                SDL_SetCursor(getCursor(_cursor));
                isHover = true;
            }
        }
        else
            element->onMouseHoverOutside(renderer);
    }

    if (!isHover && _cursor != SDL_SYSTEM_CURSOR_ARROW)
        SDL_SetCursor(getCursor(SDL_SYSTEM_CURSOR_ARROW));
}

void    PaintView::reactMouseButtonDown(const int x, const int y)
{
    SDL_Renderer*       renderer = getRenderer();

    vector<Element*>    elements = {&_paintFrame.value(), &_mainBox.value(), \
        &_toolBox.value(), &_brushSlider.value(), &_opacitySlider.value(), \
        &_colorButton.value(), &_blackButton.value(), &_whiteButton.value()};

    for (auto& element : elements)
    {
        if (!element->isAbove(x, y))
            continue;
        
        element->onMouseDown(x, y, renderer);

        break;
    }
}

void    PaintView::reactMouseButtonUp(const int x, const int y)
{
    SDL_Renderer*       renderer = getRenderer();

    vector<Element*>    elements = {&_paintFrame.value(), &_mainBox.value(), \
        &_toolBox.value(), &_brushSlider.value(), &_opacitySlider.value(), \
        &_colorButton.value(), &_blackButton.value(), &_whiteButton.value()};

    for (int i = 0; i < elements.size(); i++)
    {
        if (!elements[i]->isAbove(x, y))
            continue;

        elements[i]->onMouseUp(x, y, renderer);

        if (i == 6)
            updateColor(Color::Black);
        else if (i == 7)
            updateColor(Color::White);

        break;
    }
}

void    PaintView::reactKeyButtonDown(const int key)
{
    if (key == SDLK_F5)
        updateColor(generateRandomColor());
}

int     PaintView::reactEvent(SDL_Event* event)
{
	int		value = State::Ok;

	int		x = 0;
	int		y = 0;

	if (event->type == SDL_QUIT \
		|| (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_ESCAPE))
		return State::End;

	if (event->type == SDL_MOUSEMOTION)
		x = event->motion.x, y = event->motion.y;
	else if (event->type == SDL_MOUSEBUTTONDOWN \
		|| event->type == SDL_MOUSEBUTTONUP)
		x = event->button.x, y = event->button.y;

	if (x < 0 || x > getWidth() || y < 0 || y > getHeight())
		return State::Ok;
	else
		setX(x), setY(y);

	if (event->type == SDL_MOUSEMOTION)
		reactMouseMotion(x, y);
    
    if (event->button.button == SDL_BUTTON_LEFT)
    {
        if (event->type == SDL_MOUSEBUTTONDOWN)
            reactMouseButtonDown(x, y);
        else if (event->type == SDL_MOUSEBUTTONUP)
            reactMouseButtonUp(x, y);
    }

    if (event->type == SDL_KEYDOWN)
		reactKeyButtonDown(event->key.keysym.sym);

    update();
	refreshDisplay();

    return State::Ok;
}

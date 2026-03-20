#include "PaintSoftware.hpp"

void    PaintSoftware::reactMouseMotion(const int x, const int y)
{
    bool                isHover = false;
    SDL_Renderer*       renderer = getRenderer();

    vector<Element*>    elements = {&_paintFrame.value(), &_mainBox.value(), \
        &_toolBox.value()};

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

void    PaintSoftware::reactMouseButtonDown(const int x, const int y)
{
    SDL_Renderer*       renderer = getRenderer();

    vector<Element*>    elements = {&_paintFrame.value(), &_mainBox.value(), \
        &_toolBox.value()};

    for (auto& element : elements)
    {
        if (!element->isAbove(x, y))
            continue;
        
        element->onMouseDown(x, y, renderer);

        break;
    }
}

void    PaintSoftware::reactMouseButtonUp(const int x, const int y)
{
    SDL_Renderer*       renderer = getRenderer();

    vector<Element*>    elements = {&_paintFrame.value(), &_mainBox.value(), \
        &_toolBox.value()};

    for (auto& element : elements)
    {
        if (!element->isAbove(x, y))
            continue;

        element->onMouseUp(x, y, renderer);

        exec();

        break;
    }
}

int     PaintSoftware::reactEvent(SDL_Event* event, const int x, const int y)
{
	if (event->type == SDL_MOUSEMOTION)
		reactMouseMotion(x, y);
    
    if (event->button.button == SDL_BUTTON_LEFT)
    {
        if (event->type == SDL_MOUSEBUTTONDOWN)
            reactMouseButtonDown(x, y);
        else if (event->type == SDL_MOUSEBUTTONUP)
            reactMouseButtonUp(x, y);
    }

	refreshDisplay();

    return OK;
}

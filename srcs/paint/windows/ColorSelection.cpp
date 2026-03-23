#include "ColorSelection.hpp"

ColorSelection::ColorSelection(const int width, const int height) : \
    Window("paint-software – color selection", width, height)
{
    // ...
}

int     ColorSelection::routine(void)
{
    // ...

    return OK;
}

int     ColorSelection::waitForEvent(void)
{
    // ...

    return OK;
}

void    ColorSelection::render(void)
{
    // ...
}

int		ColorSelection::reactEvent(SDL_Event* event, const int x, const int y)
{
    // ...

    return OK;
}

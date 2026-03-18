#include "BrushOptions.hpp"

BrushOptions::BrushOptions(const int x, const int y, const int width, const int height, \
    const Color& backColor, const Color& writeColor, SDL_Renderer* renderer) : \
        Element({x, y, width, height})
{
	_brushCursors.reserve(4);
	_opacityCursors.reserve(4);

	_background.emplace(x, y, width, height, backColor, \
		true, BORDER, writeColor);

	int		globalY = H_UP_LIMIT + (DEF_BUTTON_H * 6) + (CENTER_SPACE_H * 2);
    int		lineHeights[] = {1, 2, 4, 6};

	for (int i = 0; i < 4; i++)
	{
		globalY += 35;

		Shape	line(W_LIMIT + (BRUSH_PANEL_W / 2) - BORDER, globalY, \
			BRUSH_PANEL_W / 2 - (BORDER * 2), lineHeights[i], writeColor);

		_brushLines.emplace_back(std::move(line));
	}
}

void    BrushOptions::render(SDL_Renderer* renderer)
{
    _background->render(renderer);

    // for (auto& cursor : _brushCursors)
        // cursor->render(renderer);

    // for (auto& opacities : _opacityCursors)
        // opacities.render(renderer);

    for (auto& line : _brushLines)
        line.render(renderer);

    // _opacityLine->render(renderer);
}

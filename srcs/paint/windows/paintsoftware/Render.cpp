#include "PaintSoftware.hpp"

void	PaintSoftware::render(void)
{
	SDL_Renderer*	renderer = getRenderer();

    renderBackground();

	if (!renderer)
		return;

	_paintFrame->render(renderer);

	_mainBox->render(renderer);
	_toolBox->render(renderer);

	_brushSlider->render(renderer);
	_opacitySlider->render(renderer);

	_colorText->render(renderer);
	_colorButton->render(renderer);
	_blackButton->render(renderer);
	_whiteButton->render(renderer);

	if (_endLine)
		_endLine->render(renderer);
}

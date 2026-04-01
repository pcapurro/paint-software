#include "PaintView.hpp"

void	PaintView::render(void)
{
	SDL_Renderer*	renderer = getRenderer();

    renderBackground();

	if (!renderer)
		return;

	vector<Element*>	elements = { &_paintFrame.value(), &_mainBox.value(), \
		&_toolBox.value(), &_brushSlider.value(), &_opacitySlider.value(), \
		&_colorText.value(), &_colorButton.value(), &_blackButton.value(), \
		&_whiteButton.value() };

	for (const auto element : elements)
		element->render(renderer);

	if (_endLine)
		_endLine->render(renderer);

	if (_customCursor)
		_customCursor->render(renderer);
}

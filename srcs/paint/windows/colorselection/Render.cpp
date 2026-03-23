#include "ColorSelection.hpp"

void	ColorSelection::render(void)
{
	SDL_Renderer*	renderer = getRenderer();

    renderBackground();

	if (!renderer)
		return;

	for (auto& element : _elements)
		element->render(renderer);

	_leftUpField->render(renderer);
	_leftUpError->render(renderer);

	_leftDownField->render(renderer);
	_leftDownError->render(renderer);

	_rightUpField->render(renderer);
	_rightUpError->render(renderer);

	_rightDownField->render(renderer);
	_rightDownError->render(renderer);

	_colorView->render(renderer);

	_okButton->render(renderer);
}

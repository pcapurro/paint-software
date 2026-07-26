#include "Paint.hpp"

Paint::Paint(const string& projectName, const int globalWidth, \
	const int globalHeight, const int paintWidth, const int paintHeight, \
	const int displayMode) : _displayMode(displayMode)
{
	_projectName = projectName;

	_paintWidth = paintWidth;
	_paintHeight = paintHeight;

	_paint.emplace("paint-software – " + projectName, globalWidth, \
		globalHeight, paintWidth, paintHeight, displayMode);
}

int		Paint::savePainting(const vector<Uint32>& painting) const
{
	SDL_Surface*	surface = SDL_CreateRGBSurfaceWithFormatFrom(
		const_cast<Uint32*>(painting.data()), _paintWidth, \
		_paintHeight, 32, _paintWidth * sizeof(Uint32), SDL_PIXELFORMAT_RGBA8888
	);

	if (!surface)
		return State::End;

	try {
		std::filesystem::create_directory("./paintings/");
	}
	catch (const std::filesystem::filesystem_error& e)
	{
		SDL_FreeSurface(surface);
		return State::End;
	}

	if (IMG_SavePNG(surface, string("./paintings/" + _projectName + ".png").c_str()) != 0)
	{
		SDL_FreeSurface(surface);
		return State::End;
	}

	SDL_FreeSurface(surface);

	return State::Ok;
}

int     Paint::routine(void)
{
	SDL_Event       lastEvent;
	int             value = State::Ok;

	vector<Window*>	windows = { &_paint.value(), \
		nullptr, nullptr, nullptr };

	while (true)
	{
		while (SDL_PollEvent(&lastEvent))
		{
			int	windowId = lastEvent.window.windowID;

			for (auto& window : windows)
			{
				if (!window || windowId != window->getWindowId())
					continue;

				value = window->reactEvent(&lastEvent);

				if (windowId == _paint->getWindowId())
				{
					if (value == State::End)
						return value;
					else if (value == PaintView::ColorSwitch && !_colorSelection)
					{
						_colorSelection.emplace("color selection", "materials/font/OpenSans.ttf", \
							400, 170, _displayMode, "Color selection", true, "Select a new color.");

						windows[1] = &_colorSelection.value();
					}
					else if (value == PaintView::Cancel && !_cancel)
					{
						_cancel.emplace("cancel confirmation", "materials/font/OpenSans.ttf", \
							400, 170, _displayMode, "Cancel confirmation", true, \
							"Are you sure you want to erase the painting ?", \
							vector<string>{"yes", "no"}, \
							"materials/icons/bmp/mainbox/red-cross.bmp", 45, 45);

						windows[2] = &_cancel.value();
					}
					else if (value == PaintView::Save)
					{
						int			saveValue = State::Ok;

						std::cout << "Saving '" << _projectName << ".png' to './paintings/...'" << std::endl;

						string		title, text, logo;

						saveValue = savePainting(_paint->getPaintingPixels());

						if (saveValue == State::Ok)
						{
							title = "Painting saved";
							text = "Your painting has been saved to './paintings/'.";
							logo = "materials/icons/bmp/mainbox/green-check.bmp";

							std::cout << "Painting successfuly saved." << std::endl;
						}
						else
						{
							title = "Painting not saved";
							text = "Failed to save your painting.";
							logo = "materials/icons/bmp/mainbox/red-cross.bmp";

							std::cerr << "Failed to save painting." << std::endl;
						}

						_save.emplace("save validation", "materials/font/OpenSans.ttf", \
							400, 150, _displayMode, title, true, text, vector<string>{"ok"}, logo, 45, 45);

						windows[3] = &_save.value();
					}
				}
				else if (_colorSelection && windowId == _colorSelection->getWindowId())
				{
					if (value == State::Return)
					{
						if (!_colorSelection->error())
						{
							Color	newColor = _colorSelection->getFinalColor();

							_paint->execColorSwitch(newColor);
						}
						else
							value = State::Ok;
					}

					if (value == State::End || value == State::Return)
						_colorSelection.reset(), windows[1] = nullptr;
				}
				else if (_cancel && windowId == _cancel->getWindowId())
				{
					if (value == 1)
						_paint->execCancel();

					if (value != State::Ok)
						_cancel.reset(), windows[2] = nullptr;
				}
				else if (_save && windowId == _save->getWindowId())
				{
					if (value != State::Ok)
						_save.reset(), windows[3] = nullptr;
				}
			}
		}

		for (auto& window : windows)
		{
			if (!window)
				continue;

			window->refreshDisplay();
		}

		SDL_Delay(1);
	}

    return value;
}

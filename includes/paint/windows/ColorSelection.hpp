#ifndef COLORSELECTION_HPP
# define COLORSELECTION_HPP

# include "Window.hpp"

class ColorSelection : public Window
{
    private:
        // ...

    public:
        ColorSelection(const int width, const int height);
        ~ColorSelection(void) = default;

		int     routine(void);
		int     waitForEvent(void);

		void    render(void);
		int		reactEvent(SDL_Event* event, const int x = 0, const int y = 0);

};

#endif

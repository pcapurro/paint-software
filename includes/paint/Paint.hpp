#ifndef PAINT_HPP
# define PAINT_HPP

# include "Window.hpp"

# include "Frame.hpp"

class Paint : public Window
{
    private:
        Frame           frame;

    public:
		Paint(const string& name, const int width, const int height, \
			const int frameWidth, const int frameHeight);
		~Paint(void) = default;

		int         routine(void);
		int         waitForEvent(void);

		void        render(void);
		int         reactEvent(SDL_Event* event, const int x = 0, const int y = 0);
};

#endif

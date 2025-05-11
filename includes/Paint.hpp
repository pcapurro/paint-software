#ifndef PAINT_HPP
# define PAINT_HPP

# include "Global.hpp"

# include "Window.hpp"
# include "Software.hpp"

# include "Texture.hpp"

class Paint
{
	public:
		Paint(void);
		~Paint(void);

		void	initializeSDL(void);

		void	routine(void);

	private:
		Window*				_mainWindow;
};

#endif
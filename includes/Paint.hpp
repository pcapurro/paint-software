#ifndef PAINT_HPP
# define PAINT_HPP

# include "Global.hpp"

# include "Ok.hpp"
# include "OkCancel.hpp"
# include "YesNo.hpp"
# include "Software.hpp"

# include "Texture.hpp"

class Paint
{
	public:
		Paint(void);
		~Paint(void);

		void	initializeSDL(void);

		void	routineInit(void);
		void	routine(void);

	private:
		Software*			_mainWindow;
		Window*				_otherWindow;
};

#endif
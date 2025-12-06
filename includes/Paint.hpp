#ifndef PAINT_HPP
# define PAINT_HPP

# include "Global.hpp"

# include "Ok.hpp"
# include "OkCancel.hpp"
# include "YesNo.hpp"
# include "Software.hpp"

# include "Texture.hpp"

# define PAINT_W 1500
# define PAINT_H 900

# define MAIN_TITLE "🎨 paint-software / Edit an image"

# define WELCOME_TITLE "🎨 paint-software / Welcome"
# define WELCOME_DESC "Welcome to paint-software\n\
	Project made by pcapurro\n\
	Github: github.com/pcapurro"

class Paint
{
	public:
		Paint(void) = default;
		~Paint(void);

		void	initializeSDL(void);
		void	start(void);
};

#endif

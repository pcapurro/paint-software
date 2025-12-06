#include "Global.hpp"
#include "Paint.hpp"

int	main(void)
{
	try
	{
		Paint	paint;

		paint.initializeSDL();

		paint.start();
	}
	catch (const std::exception& except)
	{
		cerr << except.what() << endl;
		return (1);
	}

	return (0);
}

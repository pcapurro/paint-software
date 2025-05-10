#ifndef OKCANCEL_HPP
# define OKCANCEL_HPP

# include "Window.hpp"

class OkCancel : public Window
{
	public:
		OkCancel(const std::string name);
		~OkCancel(void) = default;

		int		waitForEvent(void);

};

#endif
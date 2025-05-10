#ifndef YESNO_HPP
# define YESNO_HPP

# include "Window.hpp"

class YesNo : public Window
{
	public:
		YesNo(const std::string name);
		~YesNo(void) = default;

		int		waitForEvent(void);

};

#endif
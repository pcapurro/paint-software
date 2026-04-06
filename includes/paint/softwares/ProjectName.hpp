#ifndef PROJECTNAME_HPP
# define PROJECTNAME_HPP

# include "Software.hpp"

# include "DialogTextBox.hpp"

class ProjectName : public Software
{
    private:
        optional<DialogTextBox>     _window;
        string                      _name = "untitled";

    public:
        ProjectName(const int displayMode = Window::LightMode);
        ~ProjectName(void) = default;

        string                      getName(void) const;

        int                         routine(void);
};

#endif

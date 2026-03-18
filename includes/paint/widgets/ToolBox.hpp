#ifndef TOOLBOX_HPP
# define TOOLBOX_HPP

# include "Element.hpp"
# include "ImageButton.hpp"

class ToolBox : public Element
{
    private:
        vector<unique_ptr<ImageButton>>     _buttons;

    public:
        ToolBox(const int x, const int y, const int width, const int height, \
            const Color& backColor, const Color& writeColor, SDL_Renderer* renderer);

        ~ToolBox(void) = default;

        void        render(SDL_Renderer* renderer);
};

#endif

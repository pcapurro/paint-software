#ifndef TOOLBOX_HPP
# define TOOLBOX_HPP

# include "Element.hpp"
# include "ImageButton.hpp"

class ToolBox : public Element
{
    private:
        vector<unique_ptr<ImageButton>>     _buttons;

        int                                 _selectedTool = BRUSH;

        void                                initButtons(SDL_Renderer* renderer);

    public:
        ToolBox(const int x, const int y, const int width, const int height, \
            const Color& backColor, const Color& writeColor, SDL_Renderer* renderer);

        ~ToolBox(void) = default;

        int                 getSelectedTool(void) const noexcept;

        void                render(SDL_Renderer* renderer);

        virtual void        onMouseDown([[maybe_unused]] const int x = 0, [[maybe_unused]] const int y = 0, \
            [[maybe_unused]] SDL_Renderer* renderer = nullptr) override;
        virtual void        onMouseUp([[maybe_unused]] const int x = 0, [[maybe_unused]] const int y = 0, \
            [[maybe_unused]] SDL_Renderer* renderer = nullptr) override;

		virtual void        onMouseHover([[maybe_unused]] const int x = 0, [[maybe_unused]] const int y = 0, \
            [[maybe_unused]] SDL_Renderer* renderer = nullptr) override;
		virtual void        onMouseHoverOutside([[maybe_unused]] SDL_Renderer* renderer = nullptr) override;
};

#endif

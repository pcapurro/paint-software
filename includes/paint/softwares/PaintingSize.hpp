#ifndef PAINTINGSIZE_HPP
# define PAINTINGSIZE_HPP

# include "Software.hpp"

# include "PaintView.hpp"
# include "DialogValuesBox.hpp"

class PaintingSize : public Software
{
    private:
        optional<DialogValuesBox>       _window;
        vector<int>                     _values;

    public:
        PaintingSize(void);
        ~PaintingSize(void) = default;

        vector<int>                     getValues(void) const;

        int                             routine(void);
};

#endif

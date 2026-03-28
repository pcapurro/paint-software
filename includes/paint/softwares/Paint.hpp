#ifndef PAINT_HPP
# define PAINT_HPP

# include "Software.hpp"

# include "PaintView.hpp"

class Paint : public Software
{
    private:
        optional<PaintView>     _paint;

    public:
        Paint(void) = delete;
        Paint(const string& projectName, const int globalWidth, \
	        const int globalHeight, const int paintWidth, const int paintHeight);

        ~Paint(void) = default;

        int         routine(void);
};

#endif

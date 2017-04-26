#include "Pentagram.h"
#include <cmath>
#include "ShapeRendering.h"
#include "defines.h"
Pentagram::Pentagram()
    : Shape()
    , x(0)
    , y(0)
    , rotation(0)
    , r(20)
{

}

Pentagram::Pentagram(int r, int x, int y, double rotation)    : Shape()
  , x(x)
  , y(y)
  , rotation(rotation)
  , r(r)
{

}

void Pentagram::render(std::vector<Color>& pixmap, int width, int height) const
{
    static const double pi = GAME_PI;
    const double move_angle = (2*pi)/5.0;
    double cur_angle = rotation;

    circle(pixmap, Color(255,0,0), r, x, y, width);
    for(int i=0; i<5; ++i) {
        int x1 = (int)std::round(std::cos(cur_angle)*r)+x;
        int y1 = (int)std::round(std::sin(cur_angle)*r)+y;

        int x2 = (int)std::round(std::cos(cur_angle+2.0*move_angle)*r)+x;
        int y2 = (int)std::round(std::sin(cur_angle+2.0*move_angle)*r)+y;

        line(pixmap, Color(255,0,0), x1, y1, x2, y2, width);
        cur_angle+=move_angle;
    }
}

Shape*Pentagram::cloneNew() const
{
    return new Pentagram(*this);
}

#include "ShapeCar.h"
#include "ShapeRendering.h"
ShapeCar::ShapeCar(double x, double y, const Color& color) :
    color(color)
  , cx(x)
  , cy(y)
  , trunk(x-TRUNK_LENGTH/2.0, y-TRUNK_WIDTH/2.0, TRUNK_LENGTH, TRUNK_WIDTH, color)
  , wheel_b_l(0,0, WHEEL_LENGTH, WHEEL_WIDTH, Color(40,40,40))
  , wheel_b_r(0,0, WHEEL_LENGTH, WHEEL_WIDTH, Color(40,40,40))
  , wheel_t_l(0,0, WHEEL_LENGTH, WHEEL_WIDTH, Color(40,40,40))
  , wheel_t_r(0,0, WHEEL_LENGTH, WHEEL_WIDTH, Color(40,40,40))
{

}

Color ShapeCar::getColor() const
{
    return color;
}

void ShapeCar::setColor(const Color& value)
{
    color = value;
    trunk.color = value;

}

bool ShapeCar::intersects(const Rectangle& rect)
{
    return trunk.intersects(rect);
}

void ShapeCar::render(std::vector<Color>& pixmap, int pixmapWidth, int pixmapHeight) const
{
    trunk.render(pixmap, pixmapWidth, pixmapHeight);
    renderWheel(wheel_b_l, pixmap, pixmapWidth, pixmapHeight);
    renderWheel(wheel_b_r, pixmap, pixmapWidth, pixmapHeight);
    renderWheel(wheel_t_l, pixmap, pixmapWidth, pixmapHeight);
    renderWheel(wheel_t_r, pixmap, pixmapWidth, pixmapHeight);
}

Shape*ShapeCar::cloneNew() const
{
    return new ShapeCar(*this);
}

double ShapeCar::getCx() const
{
    return cx;
}

void ShapeCar::setCx(double value)
{
    cx = value;
    updateCoords();
}

double ShapeCar::getCy() const
{
    return cy;
}

void ShapeCar::setCy(double value)
{
    cy = value;
    updateCoords();
}

void ShapeCar::renderWheel(const Rectangle& wheel, std::vector<Color>& pixmap, int pixmapWidth, int pixmapHeight) const
{
    wheel.render(pixmap, pixmapWidth, pixmapHeight);
}

void ShapeCar::updateCoords()
{
    trunk.x = cx-TRUNK_LENGTH/2.0;
    trunk.y = cy-TRUNK_WIDTH/2.0;

    wheel_t_l.x = cx-WHEEL_X_OFFSET;
    wheel_t_l.y = cy-WHEEL_Y_OFFSET-WHEEL_WIDTH;

    wheel_t_r.x = cx+WHEEL_X_OFFSET;
    wheel_t_r.y = cy-WHEEL_Y_OFFSET-WHEEL_WIDTH;

    wheel_b_l.x = cx-WHEEL_X_OFFSET;
    wheel_b_l.y = cy+WHEEL_Y_OFFSET;

    wheel_b_r.x = cx+WHEEL_X_OFFSET;
    wheel_b_r.y = cy+WHEEL_Y_OFFSET;
}

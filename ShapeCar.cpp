#include "ShapeCar.h"
#include "ShapeRendering.h"
ShapeCar::ShapeCar(double x, double y, const Color& color) :
    color(color)
  , cx(x)
  , cy(y)
  , trunk(x-TRUNK_LENGTH/2.0, y-TRUNK_WIDTH/2.0, TRUNK_LENGTH, TRUNK_WIDTH, color)
{

}

bool ShapeCar::intersects(const Rectangle& rect)
{
    return trunk.intersects(rect);
}

void ShapeCar::render(std::vector<Color>& pixmap, int pixmapWidth, int pixmapHeight) const
{
    trunk.render(pixmap, pixmapWidth, pixmapHeight);
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
}

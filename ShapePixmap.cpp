#include "ShapePixmap.h"
#include "ShapeRendering.h"
ShapePixmap::ShapePixmap()
    : width(100)
    , height(100)
    , x(0)
    , y(0)

{
    drawArea.resize(width*height);
}

ShapePixmap::ShapePixmap(int width, int height, int x, int y)
    : width(width)
    , height(height)
    , x(x)
    , y(y)
{
    drawArea.resize(width*height);
}

void ShapePixmap::render(std::vector<Color>& pixmap, int width, int height) const
{
    setPixmap(pixmap, width, drawArea, x, y, width);
}

Shape* ShapePixmap::cloneNew() const
{
    return new ShapePixmap(*this);
}

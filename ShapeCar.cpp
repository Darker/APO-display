#include "ShapeCar.h"
#include "ShapeRendering.h"
ShapeCar::ShapeCar()
{

}

void ShapeCar::render(std::vector<Color>& pixmap, int pixmapWidth, int pixmapHeight) const
{
    rectangle(pixmap, color, this->width, this->height, x, y, width);
}

Shape*ShapeCar::cloneNew() const
{

}

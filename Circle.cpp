#include "circle.h"
#include "Shape.h"
#include "defines.h"
#include "ShapeRendering.h"

Circle::Circle() : Shape()
{
}

void Circle::render(std::vector<Color> &pixmap, int width, int height) const
{
    circleFill(pixmap,Color(255,0,0),40,0,0,width);
}

Shape *Circle::cloneNew() const
{
    return new Circle(*this);
}

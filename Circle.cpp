#include "Circle.h"
#include "Shape.h"
#include "defines.h"
#include "ShapeRendering.h"

Circle::Circle() : Shape()
{

}

Circle::Circle(double x,double y,int radius) : Shape()
,x(x)
,y(y)
,radius(radius)
{}
void Circle::render(std::vector<Color> &pixmap, int width, int height) const
{
    circleFill(pixmap,Color(255,0,0),radius,x,y,width);
}

Shape *Circle::cloneNew() const
{
    return new Circle(*this);
}

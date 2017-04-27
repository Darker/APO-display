#include "Platform.h"
#include "ShapeRendering.h"
#include "Shape.h"

Platform::Platform(double plength,double pwidth) :Shape()
    ,plength(plength)
    ,pwidth(pwidth)
{}
void Platform::render(std::vector<Color> &pixmap, int width, int height) const
{
    line(pixmap,Color(0,255,0),10,20,(10+pwidth),(20 + plength),width);
}
Shape *Platform::cloneNew() const
{
    return new Platform(*this);
}

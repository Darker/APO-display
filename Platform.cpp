#include "Platform.h"
#include "ShapeRendering.h"
#include "Shape.h"

Platform::Platform(double plength,double pwidth,double x, double y) :Rectangle( plength, pwidth, x, y)

{}
void Platform::render(std::vector<Color> &pixmap, int imgW, int imgH) const
{
    rectangle(pixmap, Color(0,255,0), width, height, x, y, imgW);
}
Shape *Platform::cloneNew() const
{
    return new Platform(*this);
}

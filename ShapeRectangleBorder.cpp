#include "ShapeRectangleBorder.h"

ShapeRectangleBorder::ShapeRectangleBorder() : Rectangle(0,0,10,10, Color(200,0,0)), body(0,0,0,0,Color(0,0,0)), borderWidth(0)
{

}

ShapeRectangleBorder::ShapeRectangleBorder(double x, double y, double w, double h, double bwidth, const Color& c, const Color& border_color)
{
    color = border_color;
    body.color = c;
    setX(x);
    setY(y);
    setWidth(w);
    setHeight(h);
}

Color ShapeRectangleBorder::getBorder_color() const
{
    return color;
}

void ShapeRectangleBorder::setBorder_color(const Color& value)
{
    color = value;
}

Color ShapeRectangleBorder::getBody_color() const
{
    return body.color;
}

void ShapeRectangleBorder::setBody_color(const Color& value)
{
    body.color = value;
}

int ShapeRectangleBorder::getBorderWidth() const
{
    return borderWidth;
}

void ShapeRectangleBorder::setBorderWidth(int value)
{
    borderWidth = value;
}

double ShapeRectangleBorder::setWidth(const double w)
{
    width = w;
    body.width = width-borderWidth*2;
    if(body.width<0)
        body.width = 0;
}

double ShapeRectangleBorder::setHeight(const double w)
{
    height = w;
    body.height = w-borderWidth*2;
    if(body.height<0)
        body.height = 0;
}

double ShapeRectangleBorder::setX(const double X)
{
    x = X;
    body.x = X+borderWidth;
}

double ShapeRectangleBorder::setY(const double Y)
{
    y = Y;
    body.y = Y+borderWidth;
}


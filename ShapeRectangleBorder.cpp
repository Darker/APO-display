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
    setBorderWidth(bwidth);
    recalculateBody();
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

void ShapeRectangleBorder::setWidth(const double w)
{
    width = w;
    recalculateBody();
}

void ShapeRectangleBorder::setHeight(const double w)
{
    height = w;
    recalculateBody();
}

void ShapeRectangleBorder::setX(const double X)
{
    x = X;
    recalculateBody();
}

void ShapeRectangleBorder::setY(const double Y)
{
    y = Y;
    recalculateBody();
}

void ShapeRectangleBorder::recalculateBody()
{
    body.x = x+borderWidth;
    body.y = y+borderWidth;

    body.height = height-borderWidth*2;
    if(body.height<0)
        body.height = 0;

    body.width = width-borderWidth*2;
    if(body.width<0)
        body.width = 0;
}

Shape* ShapeRectangleBorder::cloneNew() const
{
    return new ShapeRectangleBorder(*this);
}

void ShapeRectangleBorder::render(std::vector<Color>& pixmap, int pixmapWidth, int pixmapHeight) const
{
    Rectangle::render(pixmap, pixmapWidth, pixmapHeight);
    body.render(pixmap, pixmapWidth, pixmapHeight);
}


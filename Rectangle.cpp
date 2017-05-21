#include "Rectangle.h"
#include "ShapeRendering.h"
#include "Circle.h"
Rectangle::Rectangle()
    : Shape()
    , color(255,0,0)
    , x(0)
    , y(0)
    , width(10)
    , height(10)
{

}

Rectangle::Rectangle(const double x, const double y, const double width, const double height, const Color& c)
    : Shape()
    , color(c)
    , x(x)
    , y(y)
    , width(width)
    , height(height)
{

}


void Rectangle::render(std::vector<Color>& pixmap, int width, int height) const
{

    rectangle(pixmap, color, this->width, this->height, x, y, width);
}

Shape* Rectangle::cloneNew() const
{
    return new Rectangle(*this);
}

bool Rectangle::intersects(const Rectangle& other)
{
    const double x2 = x+width;
    const double y2 = y+height;
    const double otherx2 = other.x+other.width;
    const double othery2 = other.y+other.height;
    return (x2 > other.x) && (x < otherx2) &&
           (y2 > other.y) && (y < othery2);
}

bool Rectangle::intersects_left(const Circle& other)
{

    double lx = other.x - other.radius;

    if(intersects(lx,other.y))
        return true;

    return false;
}

bool Rectangle::intersects_right(const Circle& other)
{

    double lx = other.x + other.radius;

    if(intersects(lx,other.y))
        return true;

    return false;
}

bool Rectangle::intersects_up(const Circle& other)
{

    double dy = other.y + other.radius;

    if(intersects(other.x,dy))
        return true;

    return false;
}

bool Rectangle::intersects_bottom(const Circle& other)
{

    double dy = other.y - other.radius;

    if(intersects(other.x,dy))
        return true;

    return false;
}

bool Rectangle::intersects(double xp,double yp)
{
    if(xp>x && yp>y && xp<(x+width) && yp<(y + height))
        return true;
    return false;
}

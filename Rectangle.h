#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "Shape.h"
#include "Color.h"
class Rectangle : public Shape
{
public:
    Rectangle();
    Rectangle(const double x, const double y, const double width, const double height, const Color& c = Color(255,0,0));
    double x;
    double y;
    double width;
    double height;
    Color color;

    virtual void render(std::vector<Color>& pixmap, int width, int height) const override;
    virtual Shape* cloneNew() const override;

    virtual bool intersects(const Rectangle& other);

    virtual ~Rectangle() {}
};

#endif // RECTANGLE_H

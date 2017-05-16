#ifndef SHAPERECTANGLEBORDER_H
#define SHAPERECTANGLEBORDER_H
#include "Rectangle.h"

class ShapeRectangleBorder : public Rectangle
{
public:
    ShapeRectangleBorder();
    ShapeRectangleBorder(double x, double y, double w, double h, double bwidth, const Color& color, const Color& border_color);
    Color getBorder_color() const;
    void setBorder_color(const Color& value);

    Color getBody_color() const;
    void setBody_color(const Color& value);

    int getBorderWidth() const;
    void setBorderWidth(int value);

    double setWidth(const double width);
    double setHeight(const double width);
    double setX(const double X);
    double setY(const double Y);
protected:
    double borderWidth;
    // colored body inside
    Rectangle body;

};

#endif // SHAPERECTANGLEBORDER_H

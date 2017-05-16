#ifndef SHAPERECTANGLEBORDER_H
#define SHAPERECTANGLEBORDER_H
#include "Rectangle.h"

class ShapeRectangleBorder : public Rectangle
{
public:
    ShapeRectangleBorder();
    ShapeRectangleBorder(double x, double y, double w, double h, double bwidth, const Color& color, const Color& border_color);
    Color getBorder_color() const {return border_color;}
    void setBorder_color(const Color& value);

    Color getBody_color() const {return body_color;}
    void setBody_color(const Color& value);

    int getBorderWidth() const {return border_width;}
    void setBorderWidth(int value);

    double setWidth(const double width) const;
    double setHeight(const double width) const;
    double setX(const double X) const;
    double setY(const double Y) const;
protected:
    double borderWidth;
    // colored body inside
    Rectangle body;

};

#endif // SHAPERECTANGLEBORDER_H

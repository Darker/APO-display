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

    void setWidth(const double width);
    void setHeight(const double width);
    void setX(const double X);
    void setY(const double Y);

    void recalculateBody();

    virtual Shape* cloneNew() const override;
protected:
    double borderWidth;
    // colored body inside
    Rectangle body;


    // Shape interface
public:
    virtual void render(std::vector<Color>& pixmap, int pixmapWidth, int pixmapHeight) const override;
};

#endif // SHAPERECTANGLEBORDER_H

#ifndef SHAPE_H
#define SHAPE_H

#include "Color.h"
#include <string>
class Shape
{
public:
    Shape();
    virtual void render(std::vector<Color>& pixmap, int width, int height) const = 0;
    virtual Shape* cloneNew() const = 0;
    Shape(std::string name,Color color, double height, double length);
    //properties
    std::string name;
    Color color;
    double height;
    double width;

};

#endif // SHAPE_H

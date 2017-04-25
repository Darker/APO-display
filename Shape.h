#ifndef SHAPE_H
#define SHAPE_H

#include "Color.h"
class Shape
{
public:
    Shape();
    virtual void render(std::vector<Color>& pixmap, int width, int height) const = 0;
    virtual Shape* cloneNew() const = 0;
};

#endif // SHAPE_H

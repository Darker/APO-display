#ifndef SHAPE_H
#define SHAPE_H

#include "Color.h"
#include <vector>
class Shape
{
public:
    Shape();
    virtual void render(std::vector<Color>& pixmap, int width, int height) const = 0;
    virtual Shape* cloneNew() const = 0;
    // Virtual destructor ensures that all data for all
    // class implementations will be deleted
    virtual ~Shape() {}
};

#endif // SHAPE_H

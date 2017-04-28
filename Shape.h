#ifndef SHAPE_H
#define SHAPE_H

#include "Color.h"

#include <string>

#include <vector>

class Shape
{
public:

    virtual void render(std::vector<Color>& pixmap, int width, int height) const = 0;
    virtual void renderAntialiased(std::vector<Color>& pixmap, int width, int height) const {render(pixmap, width, height);}
    virtual Shape* cloneNew() const = 0;

    Shape();



    // Virtual destructor ensures that all data for all
    // class implementations will be deleted
    virtual ~Shape() {}

};

#endif // SHAPE_H

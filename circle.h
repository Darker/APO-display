#ifndef CIRCLE_H
#define CIRCLE_H
#include "Shape.h"

class Circle : public Shape
{
public:
    Circle();

    // Shape interface
public:
    void render(std::vector<Color> &pixmap, int width, int height) const;
    Shape *cloneNew() const;
};

#endif // CIRCLE_H

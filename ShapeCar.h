#ifndef SHAPECAR_H
#define SHAPECAR_H
#include "Shape.h"
class Rectangle;
class ShapeCar: public Shape
{
public:
    ShapeCar();

    double cx;
    double cy;
    bool intersects(Rectangle* rect);

    virtual void render(std::vector<Color>& pixmap, int pixmapWidth, int pixmapHeight) const override;
    virtual Shape* cloneNew() const override;
    virtual ~ShapeCar() {}
};

#endif // SHAPECAR_H

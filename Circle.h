#ifndef CIRCLE_H
#define CIRCLE_H
#include "Shape.h"

class Circle : public Shape
{
public:
    Circle();

    Circle(double x,double y,int radius );
    //properties

    double x; //x pos of center
    double y; //y pos of center
    int radius;


    // Shape interface
public:
    void render(std::vector<Color> &pixmap, int width, int height) const;
    Shape *cloneNew() const;
};

#endif // CIRCLE_H

#ifndef CIRCLE_H
#define CIRCLE_H
#include "Shape.h"

class Circle : public Shape
{
public:
    Circle();

    Circle(double x,double y, double vx, double vy, int radius );
    //properties

    double x; //x pos of center
    double y; //y pos of center
    double vx;
    double vy;
    int radius;
    double angle;


    virtual ~Circle() {}

    // Shape interface
public:
    void render(std::vector<Color> &pixmap, int width, int height) const;
    Shape *cloneNew() const;
    void move(double time);
};

#endif // CIRCLE_H

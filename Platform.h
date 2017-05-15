#ifndef BASE_H
#define BASE_H
#include "Shape.h"
#include "Rectangle.h"

//Platform for a bouncing ball
class Platform : public Rectangle
{
public:
    Platform();

    Platform(double length, double width, double x,double y);


public:
    void render(std::vector<Color> &pixmap, int width, int height) const;
    Shape *cloneNew() const;


};

#endif // BASE_H

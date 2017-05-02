#include "Circle.h"
#include "Shape.h"
#include "defines.h"
#include "ShapeRendering.h"

Circle::Circle() : Shape()
{

}

Circle::Circle(double x,double y,int radius) : Shape()
,x(x)
,y(y)
,radius(radius)
{}
void Circle::move(double vx, double vy, double time){

    if(x==GAME_WIDTH || x==0 || y==GAME_HEIGHT || y==0){
        vx=-vx;
        vy=-vy;
    }

    x+=vx*time;
    y+=vy*time;


}
void Circle::render(std::vector<Color> &pixmap, int width, int height) const
{
    circleFill(pixmap,Color(255,0,0),radius,x,y,width);
}

Shape *Circle::cloneNew() const
{
    return new Circle(*this);
}

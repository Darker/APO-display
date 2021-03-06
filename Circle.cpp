#include "Circle.h"
#include "Shape.h"
#include "defines.h"
#include "ShapeRendering.h"
#include "Platform.h"
#include <cmath>

Circle::Circle() : Shape()
{

}
Circle::Circle(double x, double y, double vx, double vy, int radius, Color c) : Shape()
,x(x)
,y(y)
,radius(radius)
,vx(vx)
,vy(vy)
,color(c)

{}

Circle::Circle(double x, double y, double vx, double vy, int radius) : Shape()
,x(x)
,y(y)
,radius(radius)
,vx(vx)
,vy(vy)
,color(Color::RED)

{}
void Circle::move(double time){
    if(y+radius+0.01>=GAME_HEIGHT || y-radius-0.01<=0){
        bounce_ceiling();
    }

    x+=vx*time;
    y+=vy*time;


}

void Circle::bounce_platform(){

    vx=vx*(-1);
    speed_up();
}

void Circle::bounce_ceiling(){

    vy=vy*(-1);
    speed_up();

}

void Circle::speed_up(){
    vx*=1.20;
    vy*=1.20;
}

int Circle::isPlayable(){

    if(x-radius<=-radius)
        return -1;
    if(x+radius>=GAME_WIDTH)
        return 1;
    return 0;
}

void Circle::render(std::vector<Color> &pixmap, int width, int height) const
{
    circleFill(pixmap,color,radius,x,y,width);
}

Shape *Circle::cloneNew() const
{
    return new Circle(*this);
}

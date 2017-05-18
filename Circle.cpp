#include "Circle.h"
#include "Shape.h"
#include "defines.h"
#include "ShapeRendering.h"
#include "Platform.h"

Circle::Circle() : Shape()
{

}

Circle::Circle(double x, double y, double vx, double vy, int radius) : Shape()
,x(x)
,y(y)
,radius(radius)
,vx(vx)
,vy(vy)

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

void Circle::bounce_ceiling(){\

    vy=vy*(-1);
    speed_up();

}

void Circle::speed_up(){
    vx*=1.25;
    vy*=1.25;
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
    circleFill(pixmap,Color(255,0,0),radius,x,y,width);
}

Shape *Circle::cloneNew() const
{
    return new Circle(*this);
}

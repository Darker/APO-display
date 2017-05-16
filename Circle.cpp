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
,angle(vy/vx)
{}
void Circle::move(double time){
    if(y>=GAME_HEIGHT || y<=0){
        bounce_ceiling();
    }

    x+=vx*time;
    y+=vy*time;


}

void Circle::bounce_platform(){

    vx=vx*(-1);
}

void Circle::bounce_ceiling(){\

    vy=vy*(-1);

}

/*bool Circle::intersects(Platform platform){
if((x+radius)>=(platform.x+platform.width) || (x-radius)>=(platform.x+platform.width) || (x+radius)>=(platform.x-platform.width)){
    return true;
}
return false;
}*/
void Circle::render(std::vector<Color> &pixmap, int width, int height) const
{
    circleFill(pixmap,Color(255,0,0),radius,x,y,width);
}

Shape *Circle::cloneNew() const
{
    return new Circle(*this);
}

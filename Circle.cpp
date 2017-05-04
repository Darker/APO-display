#include "Circle.h"
#include "Shape.h"
#include "defines.h"
#include "ShapeRendering.h"

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

    if(x>=GAME_WIDTH || x<=0 ){
        vx=vx*(-1);

    }

    if(y>=GAME_HEIGHT || y<=0){
        vy=vy*(-1);
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

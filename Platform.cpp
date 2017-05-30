#include "Platform.h"
#include "ShapeRendering.h"
#include "Shape.h"
#include "defines.h"



Platform::Platform(Color color,double plength,double pwidth,double x, double y) :Rectangle(x, y, pwidth, plength, color)

{}
void Platform::render(std::vector<Color> &pixmap, int imgW, int imgH) const
{
    rectangle(pixmap, this->color, width, height, x, y, imgW);
}
Shape *Platform::cloneNew() const
{
    return new Platform(*this);
}

void Platform::checky(){
    if (this->y + this->height > GAME_HEIGHT)
        this->y = GAME_HEIGHT - this->height;
    if (this->y  < 0)
        this->y = 0;

}

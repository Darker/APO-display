#include "ShapeRendering.h"
#include <cmath>
// Shape render implementations here
#define sgn(x) (x==0?0:(x<0?-1:1))
void setPixel(std::vector<Color>& pixmap, const Color& color, int x, int y, int width)
{
    if(x<width && x>=0 && y>=0) {
        const int pos = width*y + x;
        if(pos<pixmap.size())
            pixmap[pos] = color;
    }
}

void line(std::vector<Color>& pixmap, const Color& color, int x1, int y1, int x2, int y2, int width)
{
    //void line_fast(int x1, int y1, int x2, int y2, byte color)
    int i,dx,dy,sdx,sdy,dxabs,dyabs,x,y,px,py;

    dx=x2-x1;      /* the horizontal distance of the line */
    dy=y2-y1;      /* the vertical distance of the line */
    dxabs=std::abs(dx);
    dyabs=std::abs(dy);
    sdx=sgn(dx);
    sdy=sgn(dy);
    x=dyabs>>1;
    y=dxabs>>1;
    px=x1;
    py=y1;

    //VGA[(py<<8)+(py<<6)+px]=color;
    setPixel(pixmap, color, px, py, width);
    if (dxabs>=dyabs) /* the line is more horizontal than vertical */
    {
      for(i=0;i<dxabs;i++)
      {
        y+=dyabs;
        if (y>=dxabs)
        {
          y-=dxabs;
          py+=sdy;
        }
        px+=sdx;
        setPixel(pixmap, color, px, py, width);
      }
    }
    else /* the line is more vertical than horizontal */
    {
      for(i=0;i<dyabs;i++)
      {
        x+=dxabs;
        if (x>=dyabs)
        {
          x-=dyabs;
          px+=sdx;
        }
        py+=sdy;
        setPixel(pixmap, color, px, py, width);
      }
    }

}

void circle(std::vector<Color>& pixmap, const Color& color, int r, int x0, int y0, int width)
{
    //void drawcircle(int x0, int y0, int radius)
    //{
        int x = r;
        int y = 0;
        int err = 0;

        while (x >= y)
        {
            // filled

            //line(pixmap, color, x0 + x, y0 + y, x0 - x, y0 + y, width);
            //line(pixmap, color, x0 + y, y0 + x, x0 - y, y0 + x, width);

            //line(pixmap, color, x0 - x, y0 - y, x0 + x, y0 - y, width);
            //line(pixmap, color, x0 - y, y0 - x, x0 + y, y0 - x, width);

            setPixel(pixmap, color, x0 + x, y0 + y, width);
            setPixel(pixmap, color, x0 - x, y0 + y, width);
            setPixel(pixmap, color, x0 + y, y0 + x, width);
            setPixel(pixmap, color, x0 - y, y0 + x, width);
            setPixel(pixmap, color, x0 - x, y0 - y, width);
            setPixel(pixmap, color, x0 + x, y0 - y, width);
            setPixel(pixmap, color, x0 - y, y0 - x, width);
            setPixel(pixmap, color, x0 + y, y0 - x, width);

            if (err <= 0)
            {
                y += 1;
                err += 2*y + 1;
            }
            if (err > 0)
            {
                x -= 1;
                err -= 2*x + 1;
            }
        }
    //}
}

void circleFill(std::vector<Color>& pixmap, const Color& color, int r, int x0, int y0, int width)
{
    //void drawcircle(int x0, int y0, int radius)
    //{
        int x = r;
        int y = 0;
        int err = 0;

        while (x >= y)
        {
            // filled

            line(pixmap, color, x0 + x, y0 + y, x0 - x, y0 + y, width);
            line(pixmap, color, x0 + y, y0 + x, x0 - y, y0 + x, width);

            line(pixmap, color, x0 - x, y0 - y, x0 + x, y0 - y, width);
            line(pixmap, color, x0 - y, y0 - x, x0 + y, y0 - x, width);

//            setPixel(pixmap, color, x0 + x, y0 + y, width);
//            setPixel(pixmap, color, x0 - x, y0 + y, width);
//            setPixel(pixmap, color, x0 + y, y0 + x, width);
//            setPixel(pixmap, color, x0 - y, y0 + x, width);
//            setPixel(pixmap, color, x0 - x, y0 - y, width);
//            setPixel(pixmap, color, x0 + x, y0 - y, width);
//            setPixel(pixmap, color, x0 - y, y0 - x, width);
//            setPixel(pixmap, color, x0 + y, y0 - x, width);

            if (err <= 0)
            {
                y += 1;
                err += 2*y + 1;
            }
            if (err > 0)
            {
                x -= 1;
                err -= 2*x + 1;
            }
        }
    //}
}
void lineAngle(std::vector<Color>& pixmap, const Color& color, int x1, int y1, double angle, int length, int width)
{
    line(pixmap, color, x1, y1, (int)std::round(std::cos(angle)*length), (int)std::round(std::sin(angle)*length), width);
}
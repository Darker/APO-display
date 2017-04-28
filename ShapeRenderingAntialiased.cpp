#include "ShapeRendering.h"

#include "math.h"

inline void _dla_changebrightness(const Color from,
                  Color& to, float br)
{
  if ( br > 1.0 ) br = 1.0;
  /* linear... Maybe something more complex could give better look */
  to.r = br * (float)from.r;
  to.g = br * (float)from.g;
  to.b = br * (float)from.b;
}

//#define plot_(X,Y,D) do{ rgb_color f_;				\
//  f_.red = r; f_.green = g; f_.blue = b;			\
//  _dla_plot(img, (X), (Y), &f_, (D)) ; }while(0)

inline void _dla_plot(std::vector<Color>& pixmap, int x, int y, float br, const Color& col, int width)
{
  Color oc;
  _dla_changebrightness(col, oc, br);
  setPixel(pixmap, oc, x, y, width);
}

#define ipart_(X) ((int)(X))
#define round_(X) ((int)(((double)(X))+0.5))
#define fpart_(X) (((double)(X))-(double)ipart_(X))
#define rfpart_(X) (1.0-fpart_(X))

#define swap_(a, b) do{ __typeof__(a) tmp;  tmp = a; a = b; b = tmp; }while(0)
void line_al(std::vector<Color>& pixmap, const Color& color, int x1, int y1, int x2, int y2, int width) {

//  unsigned int x1, unsigned int y1,
//  unsigned int x2, unsigned int y2,
//  color_component r,
//  color_component g,
//  color_component b )
  double dx = (double)x2 - (double)x1;
  double dy = (double)y2 - (double)y1;
  if ( fabs(dx) > fabs(dy) ) {
    if ( x2 < x1 ) {
      swap_(x1, x2);
      swap_(y1, y2);
    }
    double gradient = dy / dx;
    double xend = round_(x1);
    double yend = y1 + gradient*(xend - x1);
    double xgap = rfpart_(x1 + 0.5);
    int xpxl1 = xend;
    int ypxl1 = ipart_(yend);
    _dla_plot(pixmap, xpxl1, ypxl1, rfpart_(yend)*xgap, color, width);
    _dla_plot(pixmap,xpxl1, ypxl1+1, fpart_(yend)*xgap, color, width);
    double intery = yend + gradient;

    xend = round_(x2);
    yend = y2 + gradient*(xend - x2);
    xgap = fpart_(x2+0.5);
    int xpxl2 = xend;
    int ypxl2 = ipart_(yend);
    _dla_plot(pixmap, xpxl2, ypxl2, rfpart_(yend) * xgap, color, width);
    _dla_plot(pixmap, xpxl2, ypxl2 + 1, fpart_(yend) * xgap, color, width);

    int x;
    for(x=xpxl1+1; x <= (xpxl2-1); x++) {
      _dla_plot(pixmap, x, ipart_(intery), rfpart_(intery), color, width);
      _dla_plot(pixmap, x, ipart_(intery) + 1, fpart_(intery), color, width);
      intery += gradient;
    }
  } else {
    if ( y2 < y1 ) {
      swap_(x1, x2);
      swap_(y1, y2);
    }
    double gradient = dx / dy;
    double yend = round_(y1);
    double xend = x1 + gradient*(yend - y1);
    double ygap = rfpart_(y1 + 0.5);
    int ypxl1 = yend;
    int xpxl1 = ipart_(xend);

    _dla_plot(pixmap, xpxl1, ypxl1, rfpart_(xend)*ygap, color, width);
    _dla_plot(pixmap,xpxl1, ypxl1+1, fpart_(xend)*ygap, color, width);
    double interx = xend + gradient;

    yend = round_(y2);
    xend = x2 + gradient*(yend - y2);
    ygap = fpart_(y2+0.5);
    int ypxl2 = yend;
    int xpxl2 = ipart_(xend);
    //plot_(xpxl2, ypxl2, rfpart_(xend) * ygap);
    //plot_(xpxl2, ypxl2 + 1, fpart_(xend) * ygap);
    _dla_plot(pixmap, xpxl2, ypxl2, rfpart_(xend) * ygap, color, width);
    _dla_plot(pixmap, xpxl2, ypxl2 + 1, fpart_(xend) * ygap, color, width);


    int y;
    for(y=ypxl1+1; y <= (ypxl2-1); y++) {
      _dla_plot(pixmap, ipart_(interx), y, rfpart_(interx), color, width);
      _dla_plot(pixmap, ipart_(interx) + 1, y, fpart_(interx), color, width);
      interx += gradient;
    }
  }
}
#undef swap_
#undef plot_
#undef ipart_
#undef fpart_
#undef round_
#undef rfpart_

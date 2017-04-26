#ifndef SHAPERENDERING_H
#define SHAPERENDERING_H
#include "Color.h"
#include <vector>
// Helper functions
void setPixel(std::vector<Color>& pixmap, const Color& color, int x, int y, int width);
void line(std::vector<Color>& pixmap, const Color& color, int x1, int y1, int x2, int y2, int width);
void lineAngle(std::vector<Color>& pixmap, const Color& color, int x1, int y1, double angle, int length, int width);
void circle(std::vector<Color>& pixmap, const Color& color, int r, int x0, int y0, int width);
void circleFill(std::vector<Color>& pixmap, const Color& color, int r, int x0, int y0, int width);
#endif // SHAPERENDERING_H

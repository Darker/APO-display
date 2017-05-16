#ifndef SHAPERENDERING_H
#define SHAPERENDERING_H
#include "Color.h"
#include <vector>
// Helper functions
void setPixel(std::vector<Color>& pixmap, const Color& color, const int x, const int y, const int pixmapWidth);
void line(std::vector<Color>& pixmap, const Color& color, const int x1, const int y1, const int x2, const int y2, const int pixmapWidth);
void lineAngle(std::vector<Color>& pixmap, const Color& color, const int x1, const int y1, double angle, const int length, const int pixmapWidth);
void circle(std::vector<Color>& pixmap, const Color& color, const int r, const int x0, const int y0, const int pixmapWidth);
void circleFill(std::vector<Color>& pixmap, const Color& color, const int r, const int x0, const int y0, const int pixmapWidth);
void setPixmap(std::vector<Color>& pixmap, const int pixmapWidth, const std::vector<Color>& sourcePixmap, const int x, const int y, const int sourceWidth);
void rectangle(std::vector<Color>& pixmap, const Color& color, const int w, const int h, int x, int y, const int pixmapWidth);

// Antialiased versions of the functions above
void line_al(std::vector<Color>& pixmap, const Color& color, const int x1, const int y1, const int x2, const int y2, const int width);

#endif // SHAPERENDERING_H

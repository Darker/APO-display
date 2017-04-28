#ifndef PENTAGRAM_H
#define PENTAGRAM_H

#include "Shape.h"
class Pentagram : public Shape
{
public:
    Pentagram();
    Pentagram(int r, int x, int y, double rotation = 0);
    virtual void render(std::vector<Color>& pixmap, int width, int height) const override;
    virtual void renderAntialiased(std::vector<Color>& pixmap, int width, int height) const override;
    virtual Shape* cloneNew() const override;

    int r;
    double rotation;
    int x;
    int y;
};

#endif // PENTAGRAM_H

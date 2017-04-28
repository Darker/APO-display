#ifndef SHAPEPIXMAP_H
#define SHAPEPIXMAP_H
#include "Shape.h"
#include <vector>
class ShapePixmap : public Shape
{
public:
    ShapePixmap();
    ShapePixmap(int width, int height, int x=0, int y=0);
    std::vector<Color> drawArea;
    const int width;
    const int height;
    int x;
    int y;

    virtual void render(std::vector<Color>& pixmap, int width, int height) const override;
    virtual Shape* cloneNew() const override;
};

#endif // SHAPEPIXMAP_H

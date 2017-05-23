#ifndef SHAPEMENUITEM_H
#define SHAPEMENUITEM_H
#include "Shape.h"
#include "ShapeText.h"
#include <memory>

class GameInterface;
class ShapeMenuItem: public Shape
{
public:
    ShapeMenuItem(const std::string& text, GameInterface* action);
    const std::string text;
    std::shared_ptr<GameInterface> const action;
    bool selected;

    void setX(const double x) {
        textItem.x = x;
    }
    void setY(const double y) {
        textItem.y = y;
    }
    double getX() const {
        return textItem.x;
    }
    double getY() const {
        return textItem.y;
    }

    virtual ~ShapeMenuItem() {}

    virtual void render(std::vector<Color>& pixmap, int pixmapWidth, int pixmapHeight) const override;
    virtual Shape* cloneNew() const override;
    void setSelected(bool value);

protected:
    ShapeText textItem;
};

#endif // SHAPEMENUITEM_H

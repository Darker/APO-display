#include "ShapeMenuItem.h"
#include "GameInterface.h"
#include "ShapeRendering.h"
#include "defines.h"

ShapeMenuItem::ShapeMenuItem(const std::string& text, GameInterface* action) :
    Shape()
  , text(text)
  , action(action)
  , selected(false)
  , textItem(text, Color::RED, 0,0, "diablo.ttf")
{

}

void ShapeMenuItem::setSelected(bool value)
{
    selected = value;
    textItem.color = selected?Color::BLACK: Color::RED;
}

void ShapeMenuItem::render(std::vector<Color>& pixmap, int pixmapWidth, int pixmapHeight) const
{
    if(selected) {
        rectangle(pixmap, Color::RED, GAME_WIDTH, 45, 0, textItem.y, pixmapWidth);
    }
    textItem.render(pixmap, pixmapWidth, pixmapHeight);
}

Shape* ShapeMenuItem::cloneNew() const
{
    return new ShapeMenuItem(*this);
}

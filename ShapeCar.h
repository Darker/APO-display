#ifndef SHAPECAR_H
#define SHAPECAR_H
#include "Shape.h"
#include "Circle.h"
#include "Rectangle.h"
class ShapeCar: public Shape
{
public:
    ShapeCar(double x, double y, const Color& color);

    Color color;
    // used to indicate wheel spinning
    uint8_t wheelSpin;

    static constexpr const double TRUNK_WIDTH = 9;
    static constexpr const double TRUNK_LENGTH = 15;
    static constexpr const double WHEEL_WIDTH = 2;
    static constexpr const double WHEEL_LENGTH = 3;
    static constexpr const double LIGHT_DIAMETER = 2;
    // coordinates relative to car center
    // top left wheel when the car faces right screen border
    static constexpr const double WHEEL_LEFT_X = -1*(TRUNK_LENGTH/3.0);
    static constexpr const double WHEEL_TOP_Y = -1*(TRUNK_WIDTH/2.0+WHEEL_WIDTH);

    // lights positions
    static constexpr const double TOP_LIGHT_Y = -1*(TRUNK_WIDTH/4.0);
    static constexpr const double BOTTOM_LIGHT_Y = -1*TOP_LIGHT_Y;

    bool intersects(const Rectangle& rect);

    virtual void render(std::vector<Color>& pixmap, int pixmapWidth, int pixmapHeight) const override;
    virtual Shape* cloneNew() const override;
    virtual ~ShapeCar() {}
    double getCx() const;
    void setCx(double value);

    double getCy() const;
    void setCy(double value);

protected:
    // car center
    double cx;
    double cy;
    void renderWheel(const Rectangle& wheel, std::vector<Color>& pixmap, int pixmapWidth, int pixmapHeight) const;
    void updateCoords();
    // subshapes
    Rectangle trunk;
    Rectangle wheel_t_l;
    Rectangle wheel_t_r;
    Rectangle wheel_b_l;
    Rectangle wheel_b_r;
    Circle top_light;
    Circle bottom_light;
};

#endif // SHAPECAR_H

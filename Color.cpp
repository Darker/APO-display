#include "Color.h"
#include <sstream>
//        const uint16_t GREEN = 0b0000011111100000;
//        const uint16_t BLUE =  0b0000000000011111;
//        const uint16_t RED =   0b1111100000000000;
const Color Color::YELLOW(255,255,0);


Color::Color(const uint16_t rgb565) 
    : r((((rgb565&RED)>>11)*255)/31)
    , g((((rgb565&GREEN)>>6)*255)/63)
    , b(((rgb565&BLUE)*255)/31) {}
Color::Color(const uint8_t r, const uint8_t g, const uint8_t b) 
    : r(r)
    , g(g)
    , b(b) {}

Color Color::operator+(const uint16_t color) const
{
    Color result(color);
    result.r+=r;
    result.g+=g;
    result.b+=b;
}

uint32_t Color::qRGBValue() const
{
    return 0xFF000000 | r<<16 | g<<8 | b;
}


Color::operator uint16_t() const {
    return ((((uint16_t)r)<<8)&RED) | ((((uint16_t)g)<<3)&GREEN) | ((((uint16_t)b>>3))&BLUE);
}
Color::operator std::string() const {
    std::stringstream s;
    s<<"RGB("<<(int)r<<", "<<(int)g<<", "<<(int)b<<")";
    return s.str();
}

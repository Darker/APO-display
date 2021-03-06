#pragma once
#include <stdint.h>
#include <string>
class Color {
    public:
        static const uint16_t GREEN565 = 0b0000011111100000;
        static const uint16_t BLUE565 =  0b0000000000011111;
        static const uint16_t RED565 =   0b1111100000000000;
        static const Color YELLOW;
        static const Color GRAY;
        static const Color WHITE;
        static const Color RED;
        static const Color GREEN;
        static const Color BLACK;
        Color() : r(0), g(0), b(0) {}
        Color(const uint16_t rgb565);
        Color(const uint8_t r, const uint8_t g, const uint8_t b);
        uint8_t r;
        uint8_t g;
        uint8_t b;
        operator uint16_t() const;
        operator std::string() const;
        Color operator+(const uint16_t color) const;
        uint16_t asRGB565() {return (uint16_t)*this;}
        uint32_t qRGBValue() const;
};

#ifdef _QT_COMPILE
#include <QtCore>
Q_DECLARE_METATYPE(Color)
#include <vector>
Q_DECLARE_METATYPE(std::vector<Color>)
#endif

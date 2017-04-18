#pragma once
#include <stdint.h>
#include <string>
class Color {
    public:
        static const uint16_t GREEN = 0b0000011111100000;
        static const uint16_t BLUE =  0b0000000000011111;
        static const uint16_t RED =   0b1111100000000000;
        Color() : r(0), g(0), b(0) {}
        Color(const uint16_t rgb565);
        Color(const uint8_t r, const uint8_t g, const uint8_t b);
        uint8_t r;
        uint8_t g;
        uint8_t b;
        operator uint16_t() const;
        operator std::string() const;
        uint16_t asRGB565() {return (uint16_t)*this;}
};

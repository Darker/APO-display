#pragma once
#include <iostream>
#include <fstream>
#include "Color.h"
class PPMReader {
    public:
        PPMReader(const char* filename);
        bool isValid() const {return file.is_open();}
        // Returns black if invalid
        virtual Color nextColor();
        // reset reader to first color
        virtual void reset();
    protected:
        std::ifstream file;
        size_t width;
        size_t height;
        // Byte where raw bytes start
        size_t startOfData;
};

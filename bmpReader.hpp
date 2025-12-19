#ifndef BMP_READER_HPP
#define BMP_READER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "color.hpp"
#include "common.hpp"

class Image_BMP {
    std::ifstream sourceFile;

    int width;
    int height;
    std::vector<Color> pixels;
    
public:
    Image_BMP();
    Image_BMP(std::string filepath);

    void setPixel(int x, int y, Color color);
    Color getPixel(int x, int y);

    int getWidth();
    int getHeight();
};

#endif
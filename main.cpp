#include "common.hpp"
#include "bmpReader.hpp"

/*
Name            FG  BG
Black           30  40
Red             31  41
Green           32  42
Yellow          33  43
Blue            34  44
Magenta         35  45
Cyan            36  46
White           37  47
Bright Black    90  100
Bright Red      91  101
Bright Green    92  102
Bright Yellow   93  103
Bright Blue     94  104
Bright Magenta  95  105
Bright Cyan     96  106
Bright White    97  107
*/

std::map<Color, int> palette = {
    {Color(0, 0, 0), 40},           // Black
    {Color(255, 0, 0), 41},         // Red
    {Color(0, 255, 0), 42},         // Green
    {Color(255, 255, 0), 43},       // Yellow
    {Color(0, 0, 255), 44},         // Blue
    {Color(255, 0, 255), 45},       // Magenta 
    {Color(0, 255, 255), 46},       // Cyan
    {Color(255, 255, 255), 47},     // White
};

std::pair<Color, int> findNearestInPalette(Color color) {
    std::pair<Color, int> nearestPaletteColor = std::pair<Color, int>(palette.begin()->first, palette.begin()->second);
    double nearestDistance = 766.0;

    for (auto paletteColor : palette) {
        double distance = std::abs((128 + (int)color.r) - (128 + (int)paletteColor.first.r)) 
                        + std::abs((128 + (int)color.g) - (128 + (int)paletteColor.first.g)) 
                        + std::abs((128 + (int)color.b) - (128 + (int)paletteColor.first.b));

        if (distance < nearestDistance) {
            nearestDistance = distance;
            nearestPaletteColor = paletteColor;
        }
    }

    return nearestPaletteColor;
}

void drawPixel(Color color) {
    std::pair<Color, int> nearestPaletteColor = findNearestInPalette(color);

    std::cout << "\033[" << std::to_string(nearestPaletteColor.second) << "m" << " " << "\033[0m";
}

int main() {
    Image_BMP image("input.bmp");

    for (int y = 0; y < image.getWidth(); ++y) {
        for (int x = 0; x < image.getHeight(); ++x) {
            drawPixel(image.getPixel(x, y));
        }
        std::cout << "\n";
    }
}


#include "common.hpp"
#include "color.hpp"

Color::Color(char a, char r, char g, char b) {
    this->a = a;
    this->r = r;
    this->g = g;
    this->b = b;
}
Color::Color(char r, char g, char b) {
    this->a = 255;
    this->r = r;
    this->g = g;
    this->b = b;
}

// LessThanComparable
bool operator<(Color color1, Color color2) 
{
    long c1 = ((long)color1.a) + ((long)color1.r) * 256 + ((long)color1.g) * 256 * 256 + ((long)color1.b) * 256 * 256 * 256;
    long c2 = ((long)color2.a) + ((long)color2.r) * 256 + ((long)color2.g) * 256 * 256 + ((long)color2.b) * 256 * 256 * 256;

    return c1 < c2;
}

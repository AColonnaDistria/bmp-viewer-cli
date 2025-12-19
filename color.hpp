#ifndef COLOR_HPP
#define COLOR_HPP

struct Color {
    char a;
    char r;
    char g;
    char b;

    Color(char a, char r, char g, char b);
    Color(char r, char g, char b);
};

bool operator<(Color color1, Color color2);

#endif
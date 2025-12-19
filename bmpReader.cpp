#include "bmpReader.hpp"
#include "color.hpp"
#include "common.hpp"
#include <cstring>

#define ID_FIELD_SIZE 2
#define BMP_SIZE_FIELD_SIZE 4
#define OFFSET_FIELD_SIZE 4
#define DIB_HEADER_SIZE_FIELD_SIZE 4

#define UNUSED_APP_SPECIFIC_FIELD_SIZE 4

#define BMP_WIDTH_FIELD_SIZE 4
#define BMP_HEIGHT_FIELD_SIZE 4

#define PIXEL_FIELD_SIZE 3
#define PADDING_FIELD_SIZE 2

Image_BMP::Image_BMP() {

}

Image_BMP::Image_BMP(std::string filepath) {
    this->sourceFile = std::ifstream(filepath);

    char idField[ID_FIELD_SIZE];
    char bmpSize[BMP_SIZE_FIELD_SIZE];
    char offsetField[OFFSET_FIELD_SIZE];  // where the pixel array starts
    char dibHeaderSize[DIB_HEADER_SIZE_FIELD_SIZE];

    char bmpWidth[BMP_WIDTH_FIELD_SIZE];
    char bmpHeight[BMP_HEIGHT_FIELD_SIZE];

    this->sourceFile.read(idField, ID_FIELD_SIZE);
    this->sourceFile.read(bmpSize, BMP_SIZE_FIELD_SIZE);
    this->sourceFile.ignore(UNUSED_APP_SPECIFIC_FIELD_SIZE);

    this->sourceFile.read(offsetField, OFFSET_FIELD_SIZE);

    // DIB Header

    this->sourceFile.read(dibHeaderSize, DIB_HEADER_SIZE_FIELD_SIZE);

    this->sourceFile.read(bmpWidth, DIB_HEADER_SIZE_FIELD_SIZE);
    this->sourceFile.read(bmpHeight, DIB_HEADER_SIZE_FIELD_SIZE);

    int bWidth;
    int bHeight;

    std::memcpy(&bWidth, bmpWidth, BMP_WIDTH_FIELD_SIZE);
    std::memcpy(&bHeight, bmpHeight, BMP_HEIGHT_FIELD_SIZE);

    this->width = bWidth;
    this->height = bHeight;

    //std::cout << "width: " << width << ", height: " << height << "\n";

    this->pixels.reserve(bWidth * bHeight);

    // jump to bitmap array
    int offset;
    std::memcpy(&offset, offsetField, OFFSET_FIELD_SIZE);

    this->sourceFile.seekg(offset);

    // read colors from bitmap array

    // bottom to top
    // left to right

    int padding = 3 - (this->width * 3 - 1) % 4;

    for (int y = this->height - 1; y >= 0; y--) {
        for (int x = 0; x < this->width; x++) {
            // read pixel
            char pixel[PIXEL_FIELD_SIZE]; // b g r

            this->sourceFile.read(pixel, PIXEL_FIELD_SIZE);
            //this->sourceFile.ignore(PADDING_FIELD_SIZE); // Padding

            setPixel(x, y, Color(pixel[2], pixel[1], pixel[0]));
        }
        
        // padding
        this->sourceFile.ignore(padding);
    }
}

void Image_BMP::setPixel(int x, int y, Color color) {
    this->pixels[this->width * y + x] = color;
}

Color Image_BMP::getPixel(int x, int y) {
    return this->pixels[this->width * y + x];
}
int Image_BMP::getWidth() {
    return this->width;
}

int Image_BMP::getHeight() {
    return this->height;
}
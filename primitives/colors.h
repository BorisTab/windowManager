#ifndef WINDOWMANAGER_COLORS_H
#define WINDOWMANAGER_COLORS_H

#include "vector3.h"

class Color {
public:
    unsigned char r = 0;
    unsigned char g = 0;
    unsigned char b = 0;
    unsigned char alpha = 255;
//    Color(): Vector3<unsigned char>() {}

    Color() = default;

    Color(unsigned char r, unsigned char g, unsigned char b, unsigned char alpha = 255):
            r(r),
            g(g),
            b(b),
            alpha(alpha) {}

   Color(uint32_t color):
         alpha((color >> 24) & 0xff),
         b((color >> 16) & 0xff), 
         g((color >> 8) & 0xff),
         r(color & 0xff) {}

    Color operator*(const Color& color) {
        return Color(r * color.r / 255, g * color.g / 255, b * color.b / 255,
                     alpha * color.alpha / 255);
    }

    Color operator+(const Color& color) {
        Color newColor;
        newColor.r = std::min(255, r + color.r);
        newColor.g = std::min(255, g + color.g);
        newColor.b = std::min(255, b + color.b);
        newColor.alpha = std::min(255, alpha + color.alpha);

        return newColor;
    }

//    Color& operator=(const Color& color) {
//        x = color.x;
//        y = color.y;
//        z = color.z;
//
//        return *this;
//    }

    uint32_t getUint32() const {
        return (r << 24) + (g << 16) + (b << 8) + alpha;
    }

    uint32_t getBackUint32() const {
        return (alpha << 24) + (b << 16) + (g << 8) + r;
    }

    bool operator==(const Color& color) {
        if (r == color.r && g == color.g && b == color.b && alpha == color.alpha)
            return true;
        return false;
    }

    Color operator*(const double intensity) {
        return Color(r * intensity, g * intensity, b * intensity, alpha);
    }
};

#endif //WINDOWMANAGER_COLORS_H

#include "primitives.h"

Point::Point(int x, int y): x(x), y(y) {}

bool Point::operator==(const Point& point) {
    return x == point.x && y == point.y;
}
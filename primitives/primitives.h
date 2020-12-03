#ifndef PRIMITIVES_WINDOWMANAGER_H
#define PRIMITIVES_WINDOWMANAGER_H

struct Point {
    int x = 0;
    int y = 0;

    Point() = default;
    Point(int x, int y);
    
    bool operator==(const Point& point);
};

#endif

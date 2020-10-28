#ifndef BASE_OBJECTS_H
#define BASE_OBJECTS_H

#include "../events/events.h"
#include "../config.h"
#include <list>

class Window {
protected:
    std::list<Window*> subWindows;

public:
    Window() = default;

    virtual void draw(Engine& engine) = 0;
    void getEvent(Event event);
};

class RectangleWindow: public Window {
protected:
    int x = 0;
    int y = 0;
    unsigned int height = 0;
    unsigned int width = 0;
    Color color;

public:
    RectangleWindow(int x, int y, int width, int height, const Color& color);
    void draw(Engine& engine) override;
};

#endif

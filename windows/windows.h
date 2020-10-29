#ifndef BASE_OBJECTS_H
#define BASE_OBJECTS_H

#include "../events/events.h"
#include "../config.h"
//#include "../events/eventQueue.h"

#include <list>

class Window {
protected:
    std::list<Window*> subWindows;

public:
    Window() = default;

    virtual void draw(Engine& engine) = 0;
    virtual void getEvent(Event& event);
};

class RectangleWindow: public Window {
public:
    int x = 0;
    int y = 0;
    int height = 0;
    int width = 0;
    Color color;

public:
    RectangleWindow(int x, int y, int width, int height, const Color& color);
    void draw(Engine& engine) override;
};

class RectButton: public RectangleWindow {
private:
//    void (*leftClickFunc)() = nullptr;

public:
    RectButton(int x, int y, int width, int height, const Color& color);

    virtual void onLeftClick() = 0;
    void getEvent(Event& event) override;
};

#endif

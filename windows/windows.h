#ifndef BASE_OBJECTS_H
#define BASE_OBJECTS_H

#include "baseWindow.h"
#include "../events/eventManager.h"

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

public:
    RectButton(int x, int y, int width, int height, const Color& color, SystemEventSender* systemEventSender);

    virtual void onLeftClick(std::unique_ptr<Event>& event) = 0;
    virtual void onLeftUnclick(std::unique_ptr<Event>& event) = 0;
    void getEvent(std::unique_ptr<Event>& event) override;
    void checkClick(std::unique_ptr<Event>& event);
};

#endif

#ifndef WINDOWMANAGER_BASEWINDOW_H
#define WINDOWMANAGER_BASEWINDOW_H

#include "../events/events.h"
#include "../config.h"
#include "../events/eventQueue.h"

#include <list>

class Window {
protected:
    std::list<Window*> subWindows;

public:
    Window() = default;

    virtual void draw(Engine& engine);
    virtual void getEvent(std::unique_ptr<Event>& event);

    void addSubWindow(Window* window);
};

#endif //WINDOWMANAGER_BASEWINDOW_H

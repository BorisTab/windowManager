#ifndef WINDOWMANAGER_EVENTQUEUE_H
#define WINDOWMANAGER_EVENTQUEUE_H

#include "events.h"
#include <queue>

class EventsQueue {
private:
    EventsQueue() = default;
    static std::queue<Event*> queue;

    friend class Application;
    friend class Window;
};

#endif //WINDOWMANAGER_EVENTQUEUE_H

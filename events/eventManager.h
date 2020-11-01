#ifndef WINDOWMANAGER_EVENTMANAGER_H
#define WINDOWMANAGER_EVENTMANAGER_H

#include <unordered_map>
#include <unordered_set>

#include "../windows/baseWindow.h"

class EventManager {
private:
    static std::unordered_map<Window*, std::unordered_set<Window*>> eventWindows;
    EventManager() = default;

public:
    static void addSender(Window* window);
    static void deleteSender(Window* window);

    static void addListener(Window* sender, Window* listener);
    static void deleteListener(Window* sender, Window* listener);
    static void deleteListenerForAll(Window* listener);

    static void sendEvent(Window* sender, Event& event);
};

class SystemEventSender: public Window {
private:
    friend class Application;
    SystemEventSender();

public:

};


#endif //WINDOWMANAGER_EVENTMANAGER_H

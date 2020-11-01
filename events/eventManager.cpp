#include "eventManager.h"

std::unordered_map<Window*, std::unordered_set<Window*>> EventManager::eventWindows;

void EventManager::addSender(Window *window) {
    eventWindows.insert({window, {}});
}

void EventManager::deleteSender(Window *window) {
    eventWindows.erase(window);
}

void EventManager::addListener(Window *sender, Window *listener) {
    eventWindows.at(sender).insert(listener);
}

void EventManager::deleteListener(Window *sender, Window *listener) {
    eventWindows.at(sender).erase(listener);
}

void EventManager::deleteListenerForAll(Window *listener) {
    for (auto& sender: eventWindows) {
        sender.second.erase(listener);
    }
}

void EventManager::sendEvent(Window *sender, std::unique_ptr<Event>& event) {
    for (auto& listener: eventWindows.at(sender)) {
        listener->getEvent(event);
    }
}

SystemEventSender::SystemEventSender() {
    EventManager::addSender(this);
}
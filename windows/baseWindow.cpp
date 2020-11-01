#include "baseWindow.h"

void Window::getEvent(Event& event) {
    for(auto window: subWindows) {
        window->getEvent(event);
    }
}

void Window::addSubWindow(Window *window) {
    subWindows.push_back(window);
}

void Window::draw(Engine &engine) {
    for (auto window: subWindows) {
        window->draw(engine);
    }
}

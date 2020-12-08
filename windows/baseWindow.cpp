#include "baseWindow.h"

void Window::getEvent(std::unique_ptr<Event>& event) {}

void Window::addSubWindow(Window *window) {
    subWindows.push_back(window);
}

void Window::drawSubWindows(Engine &engine) {
    for (auto window: subWindows) {
        window->draw(engine);
    }
}

void Window::draw(Engine &engine) {
    drawSubWindows(engine);
}

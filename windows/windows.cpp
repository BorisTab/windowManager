#include "windows.h"

RectangleWindow::RectangleWindow(int x, int y, int width, int height, const Color& color):
    x(x),
    y(y),
    width(width),
    height(height),
    color(color) {}

void RectangleWindow::draw(Engine& engine) {
    engine.drawRect(x, y, width, height, color);

    for (auto subWindow: subWindows) {
        subWindow->draw(engine);
    }
}

RectButton::RectButton(int x, int y, int width, int height, const Color &color, SystemEventSender* systemEventSender):
    RectangleWindow(x, y, width, height, color) {
    EventManager::addListener(systemEventSender, this);
}

void RectButton::getEvent(Event &event) {
    if (event.type == Event::MouseClicked) {
        int clickX = dynamic_cast<MouseEvent&>(event).x;
        int clickY = dynamic_cast<MouseEvent&>(event).y;

        if (clickX >= x && clickX <= x + width && clickY >= y && clickY <= y + height) {
            onLeftClick(event);
        }

    } else if (event.type == Event::MouseUnclicked)
        onLeftUnclick(event);

    for (auto window: subWindows) {
        window->getEvent(event);
    }
}

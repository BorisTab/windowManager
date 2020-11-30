#include "windows.h"

RectangleWindow::RectangleWindow(int x, int y, int width, int height, const Color& color):
    x(x),
    y(y),
    width(width),
    height(height),
    color(color) {}

void RectangleWindow::draw(Engine& engine) {
    engine.drawRect(x, y, width, height, color);

    drawSubWindows(engine);
}

RectButton::RectButton(int x, int y, int width, int height, const Color &color, SystemEventSender* systemEventSender):
    RectangleWindow(x, y, width, height, color) {
    EventManager::addListener(systemEventSender, this);
}

void RectButton::checkClick(std::unique_ptr<Event>& event) {
    if (event->type == Event::MouseClicked) {
        int clickX = dynamic_cast<MouseEvent*>(event.get())->x;
        int clickY = dynamic_cast<MouseEvent*>(event.get())->y;

        if (clickX >= x && clickX <= x + width && clickY >= y && clickY <= y + height) {
            onLeftClick(event);
        }

    } else if (event->type == Event::MouseUnclicked)
        onLeftUnclick(event);
}

void RectButton::getEvent(std::unique_ptr<Event>& event) {
    checkClick(event);

    for (auto window: subWindows) {
        window->getEvent(event);
    }
}

Text::Text(int x, int y, const std::string& text):
     x(x),
     y(y),
     text(text) {}

void Text::setFont(const std::string& pathToFont) {
    fontPath = pathToFont;
}

void Text::setFontSize(int size) {
    fontSize = size;
}

void Text::draw(Engine &engine) {
    engine.drawText(x, y, text, fontPath, fontSize);
    drawSubWindows(engine);
}

#include "windows.h"

void Window::getEvent(Event& event) {}

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

RectButton::RectButton(int x, int y, int width, int height, const Color &color):
        RectangleWindow(x, y, width, height, color) {}

//void RectButton::onLeftClick(void (*clickFunction)()) {
//    leftClickFunc = clickFunction;
//}

void RectButton::getEvent(Event &event) {
    if (event.type == Event::MouseClicked) {
        int clickX = event.mouseClick.x;
        int clickY = event.mouseClick.y;

        if (clickX >= x && clickX <= x + width && clickY >= y && clickY <= y + height) {
            if (event.mouseClick.button == Mouse::LeftButton)
                onLeftClick();
        }
    }

    for (auto window: subWindows) {
        window->getEvent(event);
    }
}

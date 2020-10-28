#include "windows.h"

void Window::getEvent(Event event) {

}

RectangleWindow::RectangleWindow(int x, int y, int width, int height, const Color& color):
    x(x),
    y(y),
    width(width),
    height(height),
    color(color) {}

void RectangleWindow::draw(Engine& engine) {
    engine.drawRect(x, y, width, height, color);
}

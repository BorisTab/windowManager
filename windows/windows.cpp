#include "windows.h"

RectangleWindow::RectangleWindow(int x, int y, int width, int height, const Color& color):
    x(x),
    y(y),
    width(width),
    height(height),
    color(color),
    imageName("") {}

RectangleWindow::RectangleWindow(int x, int y, int width, int height, 
                                 const Color& color,
                                 const std::string& imageName):
    x(x),
    y(y),
    width(width),
    height(height),
    color(color), 
    imageName(imageName) {}

void RectangleWindow::draw(Engine& engine) {
    engine.drawRect(x, y, width, height, color, imageName);

    drawSubWindows(engine);
}

RectButton::RectButton(int x, int y, int width, int height, 
                       const Color &color, 
                       SystemEventSender* systemEventSender,
                       const std::string& imageName):
    RectangleWindow(x, y, width, height, color, imageName) {
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
}

RectMoveable::RectMoveable(int x, int y, int width, int height, 
                           const Color& color, 
                           SystemEventSender* systemEventSender,
                           const std::string& imageName):
    RectButton(x, y, width, height, color, systemEventSender, imageName) {}

void RectMoveable::getEvent(std::unique_ptr<Event>& event) {
    RectButton::getEvent(event);
    
    if (Event::MouseMoved == event->type && mousePressed)
        onMouseMove(event);
}

void RectMoveable::onLeftClick(std::unique_ptr<Event>& event) {
    mousePressed = true;
}

void RectMoveable::onLeftUnclick(std::unique_ptr<Event>& event) {
    mousePressed = false;
}

RectPixelButton::RectPixelButton(int x, int y, int width, int height, 
                                 const Color& color, 
                                 SystemEventSender* systemEventSender):
                RectButton(x, y, width, height, color, systemEventSender),
                pixels(height, std::vector<Color>(width, color)) {}

void RectPixelButton::draw(Engine& engine) {
    engine.drawPixels(x, y, pixels);

    drawSubWindows(engine);
}

void RectPixelButton::setPixels(uint32_t* newPixels, int width, int height) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            pixels[y][x] = Color(newPixels[y * width + x]);
        }
    }
}

std::vector<std::vector<Color>>& RectPixelButton::getPixels() {
    return pixels;
}

Text::Text(int x, int y, const std::string& text,
           const std::string& fontName,
           int fontSize, 
           const Color& color):
     x(x),
     y(y),
     text(text),
     font(fontName),
     fontSize(fontSize),
     color(color) {}

void Text::setFont(const std::string& fontName) {
    font = fontName;
}

void Text::setFontSize(int size) {
    fontSize = size;
}

void Text::draw(Engine &engine) {
    engine.drawText(x, y, text, font, fontSize, color);
    drawSubWindows(engine);
}

#include "sliderPointer.h"

Slider::Slider(int x, int y, int width, int height,
               const Color& color, 
               SystemEventSender* systemEventSender, 
               int minPos, int maxPos,
               bool vertical):
               RectMoveable(x, y, width, height, 
                            color, systemEventSender),
               minPos(minPos),
               maxPos(maxPos),
               vertical(vertical) {}

double Slider::insideCheck(double pos) {
    pos = std::max(pos, minPos);
    pos = std::min(pos, maxPos);

    return pos;
}

void Slider::onMouseMove(std::unique_ptr<Event>& event) {
    double newPos = 0;
    if (vertical) {
        newPos = insideCheck(dynamic_cast<MouseEvent*>(event.get())->y);
        y = newPos - height / 2;
    }
    else {
        newPos = insideCheck(dynamic_cast<MouseEvent*>(event.get())->x);
        x = newPos - width / 2;
    }
    
    value = (newPos - minPos) / (maxPos - minPos);

    sendMoveEvent();
}

void Slider::onLeftClick(std::unique_ptr<Event>& event) {
    RectMoveable::onLeftClick(event);
    onMouseMove(event);
}

void Slider::sendMoveEvent() {
    auto sliderMoveEvent = new SliderMoveEvent;
    sliderMoveEvent->yValue = value;

    auto uniquePtrEvent = std::unique_ptr<Event>(sliderMoveEvent);
    EventManager::sendEvent(this, uniquePtrEvent);
}

SliderMoveEvent::SliderMoveEvent() {
    type = Event::SliderMoved;
}

PointerMoveEvent::PointerMoveEvent() {
    type = Event::PointerMoved;
}

Pointer::Pointer(int x, int y, int width, int height,
                 const Color& color, 
                 SystemEventSender* systemEventSender, 
                 int minX, int maxX, 
                 int minY, int maxY):
    RectMoveable(x, y, width, height, color, systemEventSender),
    minX(minX), maxX(maxX),
    minY(minY), maxY(maxY) {}

Point Pointer::insideCheck(double x, double y) {
    x = std::min(x, maxX);
    x = std::max(x, minX);

    y = std::min(y, maxY);
    y = std::max(y, minY);

    return {static_cast<int>(x), static_cast<int>(y)};
}

void Pointer::onMouseMove(std::unique_ptr<Event>& event) {
    auto mouseEvent = dynamic_cast<MouseEvent*>(event.get());
    Point newPoint = insideCheck(mouseEvent->x, mouseEvent->y);
    
    x = newPoint.x - width / 2;
    y = newPoint.y - height / 2; 

    xValue = (newPoint.x - minX) / (maxX - minX);
    yValue = (newPoint.y - minY) / (maxY - minY);

    sendMoveEvent();
}

void Pointer::onLeftClick(std::unique_ptr<Event>& event) {
    RectMoveable::onLeftClick(event);
    onMouseMove(event);
}

void Pointer::sendMoveEvent() {
    auto pointerMoveEvent = new PointerMoveEvent;
    pointerMoveEvent->yValue = yValue;
    pointerMoveEvent->xValue = xValue;

    auto uniquePtrEvent = std::unique_ptr<Event>(pointerMoveEvent);
    EventManager::sendEvent(this, uniquePtrEvent);
}

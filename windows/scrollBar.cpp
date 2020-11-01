#include "scrollBar.h"

ScrollBar::ScrollBar(int x, int y, int width, int height, SystemEventSender *systemEventSender):
        scrollBarUpButton(x, y, width, width, Color(77, 0, 153), systemEventSender),
        scrollBarDownButton(x, y + height - width, width, width, Color(77, 0, 153), systemEventSender),
        scrollBarContainer(x, y + width, width, height - 2 * width, Color(128, 128, 128), systemEventSender),
        scrollBarSlider(x, y + width, width, 2 * width, Color(255, 165, 0), systemEventSender) {

    subWindows.push_back(&scrollBarDownButton);
    subWindows.push_back(&scrollBarUpButton);
    subWindows.push_back(&scrollBarContainer);
    subWindows.push_back(&scrollBarSlider);

//    EventManager::addSender(this);
//    EventManager::addSender(&scrollBarUpButton);
//    EventManager::addSender(&scrollBarDownButton);
//    EventManager::addSender(&scrollBarSlider);

}

//void ScrollBarDownButton::onLeftClick() {
//    Event event;
//    event.type = Event::ScrollBarEvent;
//    event.scrollBar.id =
//}
//
//void ScrollBarSlider::getEvent(Event &event) {
//    if (event.type == Event::MouseMoved && ScrollBar::sliderPressed == true) {
//        y = event.mouseMove.y - height / 2;
//    }
//}

void ScrollBarSlider::onLeftClick(Event& event) {
    color = Color(204, 133, 0);
}

void ScrollBarSlider::onLeftUnclick(Event &event) {
    color = Color(255, 165, 0);
}

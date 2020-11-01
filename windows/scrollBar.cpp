#include "scrollBar.h"

ScrollUpButtonPressedEvent::ScrollUpButtonPressedEvent() {
    type = ScrollUpButtonClicked;
}

ScrollDownButtonPressedEvent::ScrollDownButtonPressedEvent() {
    type = ScrollDownButtonClicked;
}

ScrollUpButtonEvent::ScrollUpButtonEvent() {
    type = ScrollUpButton;
}

ScrollDownButtonEvent::ScrollDownButtonEvent() {
    type = ScrollDownButton;
}

ScrollMouseMoveEvent::ScrollMouseMoveEvent() {
    type = ScrollMouseMoved;
}

ScrollBar::ScrollBar(int x, int y, int width, int height, SystemEventSender *systemEventSender):
        scrollBarUpButton(x, y, width, width, Color(77, 0, 153), systemEventSender),
        scrollBarDownButton(x, y + height - width, width, width, Color(77, 0, 153), systemEventSender),
        scrollBarContainer(x, y + width, width, height - 2 * width, Color(128, 128, 128), systemEventSender),
        scrollBarSlider(x, y + width, width, 2 * width, Color(255, 165, 0), systemEventSender) {

    minSliderPos = y + width;
    maxSliderPos = y + height - width;

    subWindows.push_back(&scrollBarDownButton);
    subWindows.push_back(&scrollBarUpButton);
    subWindows.push_back(&scrollBarContainer);
    subWindows.push_back(&scrollBarSlider);

    EventManager::addListener(systemEventSender, this);

    EventManager::addSender(this);
    EventManager::addSender(&scrollBarContainer);
    EventManager::addSender(&scrollBarUpButton);
    EventManager::addSender(&scrollBarDownButton);
    EventManager::addSender(&scrollBarSlider);

    EventManager::addListener(&scrollBarDownButton, this);
    EventManager::addListener(&scrollBarUpButton, this);
    EventManager::addListener(&scrollBarSlider, this);
    EventManager::addListener(&scrollBarContainer, this);

    EventManager::addListener(this, &scrollBarDownButton);
    EventManager::addListener(this, &scrollBarUpButton);
    EventManager::addListener(this, &scrollBarSlider);
    EventManager::addListener(this, &scrollBarContainer);
}

void ScrollBar::getEvent(std::unique_ptr<Event>& event) {
    if (event->type == Event::ScrollDownButtonClicked) {
        auto barEvent = new ScrollDownButtonEvent;
        barEvent->maxY = maxSliderPos;

        auto uniquePtrEvent = std::unique_ptr<Event>(barEvent);
        EventManager::sendEvent(this, uniquePtrEvent);
    }
    else if (event->type == Event::ScrollUpButtonClicked) {
        auto barEvent = new ScrollUpButtonEvent;
        barEvent->minY = minSliderPos;

        auto uniquePtrEvent = std::unique_ptr<Event>(barEvent);
        EventManager::sendEvent(this, uniquePtrEvent);
    }
    else if (event->type == Event::ScrollSliderClicked) {
        sliderPressed = true;
    }
    else if (event->type == Event::ScrollSliderUnclicked) {
        sliderPressed = false;
    }
    else if (event->type == Event::MouseMoved) {
        auto barEvent = new ScrollMouseMoveEvent;
        barEvent->sliderPressed = sliderPressed;
        barEvent->mousePosY = dynamic_cast<MouseEvent*>(event.get())->y;
        barEvent->minY = minSliderPos;
        barEvent->maxY = maxSliderPos;

        auto uniquePtrEvent = std::unique_ptr<Event>(barEvent);
        EventManager::sendEvent(this, uniquePtrEvent);
    }
}

void ScrollBarDownButton::onLeftClick(std::unique_ptr<Event>& event) {
    auto scrollEvent = new ScrollDownButtonPressedEvent;

    auto uniquePtrEvent = std::unique_ptr<Event>(scrollEvent);
    EventManager::sendEvent(this, uniquePtrEvent);
}

void ScrollBarUpButton::onLeftClick(std::unique_ptr<Event>& event) {
    auto scrollEvent = new ScrollUpButtonPressedEvent;

    auto uniquePtrEvent = std::unique_ptr<Event>(scrollEvent);
    EventManager::sendEvent(this, uniquePtrEvent);
}

void ScrollBarSlider::getEvent(std::unique_ptr<Event>& event) {
    if (event->type == Event::ScrollDownButton) {
        int maxY = dynamic_cast<ScrollDownButtonEvent*>(event.get())->maxY;
        if (y <  maxY - height - 5)
            y += 5;
        else
            y = maxY - height;
    }
    else if (event->type == Event::ScrollUpButton) {
        int minY = dynamic_cast<ScrollUpButtonEvent*>(event.get())->minY;
        if (y >  minY + 5)
            y -= 5;
        else
            y = minY;
    }
    else if (event->type == Event::ScrollMouseMoved) {
        auto barEvent = dynamic_cast<ScrollMouseMoveEvent*>(event.get());

        if (barEvent->sliderPressed) {
//            int diff = barEvent->mousePosY - y;
            y = barEvent->mousePosY - beginUpDifference;

            if (y < barEvent->minY)
                y = barEvent->minY;
            else if (y > barEvent->maxY - height)
                y = barEvent->maxY - height;
        }
    }
    else
        checkClick(event);
}

void ScrollBarSlider::onLeftClick(std::unique_ptr<Event>& event) {
    color = Color(204, 133, 0);

    auto sliderEvent = new ScrollSliderEvent;
    sliderEvent->type = Event::ScrollSliderClicked;
//    sliderEvent->upDifference = dynamic_cast<MouseEvent*>(event.get())->y - y;
    beginUpDifference = dynamic_cast<MouseEvent*>(event.get())->y - y;

    auto uniquePtrEvent = std::unique_ptr<Event>(sliderEvent);
    EventManager::sendEvent(this, uniquePtrEvent);
}

void ScrollBarSlider::onLeftUnclick(std::unique_ptr<Event>& event) {
    color = Color(255, 165, 0);

    auto sliderEvent = new ScrollSliderEvent;
    sliderEvent->type = Event::ScrollSliderUnclicked;

    auto uniquePtrEvent = std::unique_ptr<Event>(sliderEvent);
    EventManager::sendEvent(this, uniquePtrEvent);
}

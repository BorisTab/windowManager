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

ScrollContainerClickEvent::ScrollContainerClickEvent() {
    type = ScrollContainerClicked;
}

ScrollBarActionEvent::ScrollBarActionEvent() {
    type = ScrollBarAction;
}

ScrollGetSliderPosEvent::ScrollGetSliderPosEvent() {
    type = ScrollGetSliderPos;
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

void ScrollBar::setButtonsColor(const Color &color) {
    scrollBarUpButton.color = color;
    scrollBarDownButton.color = color;
}

void ScrollBar::setContainerColor(const Color &color) {
    scrollBarContainer.color = color;
}

void ScrollBar::setSliderColor(const Color &color, const Color &clickedColor) {
    scrollBarSlider.color = color;
    scrollBarSlider.clickedColor = clickedColor;
}

void ScrollBar::scrollDownButtonEventCreate(std::unique_ptr<Event> &event) {
    auto barEvent = new ScrollDownButtonEvent;
    barEvent->maxY = maxSliderPos;

    auto uniquePtrEvent = std::unique_ptr<Event>(barEvent);
    EventManager::sendEvent(this, uniquePtrEvent);
}

void ScrollBar::scrollUpButtonEventCreate(std::unique_ptr<Event> &event) {
    auto barEvent = new ScrollUpButtonEvent;
    barEvent->minY = minSliderPos;

    auto uniquePtrEvent = std::unique_ptr<Event>(barEvent);
    EventManager::sendEvent(this, uniquePtrEvent);
}

void ScrollBar::scrollContainerClickedEventCreate(std::unique_ptr<Event> &event) {
    auto ptr = dynamic_cast<ScrollContainerClickEvent*>(event.get());
    ptr->maxY = maxSliderPos;
    ptr->minY = minSliderPos;

    EventManager::sendEvent(this, event);
}

void ScrollBar::getEvent(std::unique_ptr<Event>& event) {
    if (event->type == Event::ScrollDownButtonClicked) {
        scrollDownButtonEventCreate(event);
    }
    else if (event->type == Event::ScrollUpButtonClicked) {
        scrollUpButtonEventCreate(event);
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
    else if (event->type == Event::ScrollContainerClicked) {
        scrollContainerClickedEventCreate(event);
    }
    else if (event->type == Event::KeyClicked) {
        auto keyEvent = dynamic_cast<KeyEvent*>(event.get());
        if (keyEvent->ctrl && keyEvent->key == KeyEvent::Down)
            scrollDownButtonEventCreate(event);
        if (keyEvent->ctrl && keyEvent->key == KeyEvent::Up)
            scrollUpButtonEventCreate(event);
    }


    if (event->type == Event::ScrollGetSliderPos) {
        auto scrollAction = new ScrollBarActionEvent;
        auto scrollGet = dynamic_cast<ScrollGetSliderPosEvent*>(event.get());

        int sliderPos = scrollGet->sliderPos;
        scrollAction->diff =  sliderPos - sliderLastPos;
        scrollAction->percent =(sliderPos - minSliderPos + 0.0) / (maxSliderPos - scrollGet->height - minSliderPos);

        if (scrollAction->diff != 0) {
            sliderLastPos = sliderPos;

            auto scrollActionUniq = std::unique_ptr<Event>(scrollAction);
            EventManager::sendEvent(this, scrollActionUniq);
        }

        return;
    }

    auto getSliderPos = std::unique_ptr<Event>(new ScrollGetSliderPosEvent);
    EventManager::sendEvent(this, getSliderPos);
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
            y = barEvent->mousePosY - beginUpDifference;

            if (y < barEvent->minY)
                y = barEvent->minY;
            else if (y > barEvent->maxY - height)
                y = barEvent->maxY - height;
        }
    }
    else if (event->type == Event::ScrollContainerClicked) {
        auto barEvent = dynamic_cast<ScrollContainerClickEvent*>(event.get());

        if (barEvent->mousePosY < y)
            y -= 50;
        else if (barEvent->mousePosY > y + height)
            y += 50;

        if (y < barEvent->minY)
            y = barEvent->minY;
        else if (y > barEvent->maxY - height)
            y = barEvent->maxY - height;
    }
    else if (event->type == Event::ScrollGetSliderPos) {
        auto getEvent = dynamic_cast<ScrollGetSliderPosEvent*>(event.get());
        getEvent->sliderPos = y;
        getEvent->height = height;

        EventManager::sendEvent(this, event);
    }
    else
        checkClick(event);
}

void ScrollBarSlider::onLeftClick(std::unique_ptr<Event>& event) {
    color = clickedColor;

    auto sliderEvent = new ScrollSliderEvent;
    sliderEvent->type = Event::ScrollSliderClicked;
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

void ScrollBarContainer::onLeftClick(std::unique_ptr<Event> &event) {
    auto sliderEvent = new ScrollContainerClickEvent;
    sliderEvent->mousePosY = dynamic_cast<MouseEvent*>(event.get())->y;

    auto uniquePtrEvent = std::unique_ptr<Event>(sliderEvent);
    EventManager::sendEvent(this, uniquePtrEvent);
}

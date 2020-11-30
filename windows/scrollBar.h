#ifndef WINDOWMANAGER_SCROLLBAR_H
#define WINDOWMANAGER_SCROLLBAR_H

#include "windows.h"

class ScrollBarUpButton: RectButton {
private:
    friend class ScrollBar;

    ScrollBarUpButton(int x, int y, int width, int height, const Color& color, SystemEventSender* systemEventSender):
            RectButton(x, y, width, height, color, systemEventSender) {}

    void onLeftClick(std::unique_ptr<Event>& event) override;

    void onLeftUnclick(std::unique_ptr<Event>& event) override {}
};

class ScrollBarDownButton: RectButton {
private:
    friend class ScrollBar;

    ScrollBarDownButton(int x, int y, int width, int height, const Color& color, SystemEventSender* systemEventSender):
            RectButton(x, y, width, height, color, systemEventSender) {}

    void onLeftClick(std::unique_ptr<Event>& event) override;

    void onLeftUnclick(std::unique_ptr<Event>& event) override {}
};

class ScrollBarSlider: RectButton {
private:
    friend class ScrollBar;

    int beginUpDifference = 0;
    Color clickedColor = Color(204, 133, 0);

    ScrollBarSlider(int x, int y, int width, int height, const Color& color, SystemEventSender* systemEventSender):
            RectButton(x, y, width, height, color, systemEventSender) {}

    void onLeftClick(std::unique_ptr<Event>& event) override;
    void onLeftUnclick(std::unique_ptr<Event>& event) override;

public:
    void getEvent(std::unique_ptr<Event>& event) override;
};

class ScrollBarContainer: RectButton {
private:
    friend class ScrollBar;

    ScrollBarContainer(int x, int y, int width, int height, const Color& color, SystemEventSender* systemEventSender):
            RectButton(x, y, width, height, color, systemEventSender) {}

    void onLeftClick(std::unique_ptr<Event>& event) override;

    void onLeftUnclick(std::unique_ptr<Event>& event) override {}
};

class ScrollBar: public Window {
private:
    ScrollBarContainer scrollBarContainer;
    ScrollBarUpButton scrollBarUpButton;
    ScrollBarDownButton scrollBarDownButton;
    ScrollBarSlider scrollBarSlider;

    int maxSliderPos = 0;
    int minSliderPos = 0;
    int sliderLastPos = 0;

    bool sliderPressed = false;

public:
    ScrollBar(int x, int y, int width, int height, SystemEventSender* systemEventSender);

    void getEvent(std::unique_ptr<Event>& event) override;

    void setSliderColor(const Color& color, const Color& clickedColor);
    void setButtonsColor(const Color& color);
    void setContainerColor(const Color& color);

    void scrollDownButtonEventCreate(std::unique_ptr<Event>& event);
    void scrollUpButtonEventCreate(std::unique_ptr<Event>& event);
    void scrollContainerClickedEventCreate(std::unique_ptr<Event>& event);
};

struct ScrollUpButtonPressedEvent: public Event {
    ScrollUpButtonPressedEvent();
};

struct ScrollDownButtonPressedEvent: public Event {
    ScrollDownButtonPressedEvent();
};

struct ScrollUpButtonEvent: public Event {
    int minY = 0;
    ScrollUpButtonEvent();
};


struct ScrollDownButtonEvent: public Event {
    int maxY = 0;
    ScrollDownButtonEvent();
};

struct ScrollSliderEvent: public Event {};

struct ScrollMouseMoveEvent: public Event {
    bool sliderPressed = false;
    int minY = 0;
    int maxY = 0;
    int mousePosY = 0;
    int sliderPos = 0;
    ScrollMouseMoveEvent();
};

struct ScrollContainerClickEvent: public Event {
    int mousePosY = 0;
    int minY = 0;
    int maxY = 0;
    ScrollContainerClickEvent();
};

struct ScrollBarActionEvent: public Event {
    int diff = 0;
    float percent = 0;

    enum Action {
        ScrolledUp,
        ScrolledDown
    };
    Action action;

    ScrollBarActionEvent();
};

struct ScrollGetSliderPosEvent: public Event {
    int sliderPos = 0;
    int height = 0;

    ScrollGetSliderPosEvent();
};

#endif //WINDOWMANAGER_SCROLLBAR_H

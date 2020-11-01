#ifndef WINDOWMANAGER_SCROLLBAR_H
#define WINDOWMANAGER_SCROLLBAR_H

#include "windows.h"

class ScrollBarUpButton: RectButton {
private:
    friend class ScrollBar;

    ScrollBarUpButton(int x, int y, int width, int height, const Color& color, SystemEventSender* systemEventSender):
            RectButton(x, y, width, height, color, systemEventSender) {}

    void onLeftClick(Event& event) override;

    void onLeftUnclick(Event& event) override {

    }
};

class ScrollBarDownButton: RectButton {
private:
    friend class ScrollBar;

    ScrollBarDownButton(int x, int y, int width, int height, const Color& color, SystemEventSender* systemEventSender):
            RectButton(x, y, width, height, color, systemEventSender) {}

    void onLeftClick(Event& event) override;

    void onLeftUnclick(Event& event) override {}
};

class ScrollBarSlider: RectButton {
private:
    friend class ScrollBar;

    ScrollBarSlider(int x, int y, int width, int height, const Color& color, SystemEventSender* systemEventSender):
            RectButton(x, y, width, height, color, systemEventSender) {}

    void onLeftClick(Event& event) override;
    void onLeftUnclick(Event& event) override;

public:
    void getEvent(Event &event) override;
};

class ScrollBarContainer: RectButton {
private:
    friend class ScrollBar;

    ScrollBarContainer(int x, int y, int width, int height, const Color& color, SystemEventSender* systemEventSender):
            RectButton(x, y, width, height, color, systemEventSender) {}

    void onLeftClick(Event& event) override {

    }

    void onLeftUnclick(Event& event) override {

    }
};

class ScrollBar: public Window {
private:
    ScrollBarContainer scrollBarContainer;
    ScrollBarUpButton scrollBarUpButton;
    ScrollBarDownButton scrollBarDownButton;
    ScrollBarSlider scrollBarSlider;

    int maxSliderPos = 0;
    int minSliderPos = 0;

//    int sliderPos = 0;
    bool sliderPressed = false;

public:
    ScrollBar(int x, int y, int width, int height, SystemEventSender* systemEventSender);

    void getEvent(Event &event) override;
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
    ScrollMouseMoveEvent();
};

#endif //WINDOWMANAGER_SCROLLBAR_H

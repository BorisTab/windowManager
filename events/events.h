#ifndef EVENTS_H
#define EVENTS_H

class Event {
public:
    enum EventType {
        Idle,
        MouseClicked,
        MouseUnclicked,
        MouseMoved,
        Closed,
        ScrollUpButtonClicked,
        ScrollDownButtonClicked,
        ScrollUpButton,
        ScrollDownButton,
        ScrollSliderClicked,
        ScrollSliderUnclicked,
        ScrollMouseMoved,
        ScrollContainerClicked
    };

    virtual ~Event() = default;

    EventType type;
};

class MouseEvent: public Event {
public:
    enum Button {
        LeftButton,
        RightButton
    };

    int x = 0;
    int y = 0;
    Button button;
};

#endif
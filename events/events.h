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
        ScrollMouseMoved
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

    int x;
    int y;
    Button button;
};

#endif
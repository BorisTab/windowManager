#ifndef EVENTS_H
#define EVENTS_H

class Event {
public:
    enum EventType {
        Idle,
        MouseClicked,
        MouseUnclicked,
        MouseMoved,
        KeyClicked,
        Closed,
        ScrollUpButtonClicked,
        ScrollDownButtonClicked,
        ScrollUpButton,
        ScrollDownButton,
        ScrollSliderClicked,
        ScrollSliderUnclicked,
        ScrollMouseMoved,
        ScrollContainerClicked,
        ScrollBarAction
    };

    virtual ~Event() = default;

    EventType type;
};

struct MouseEvent: public Event {
    enum Button {
        LeftButton,
        RightButton
    };

    int x = 0;
    int y = 0;
    Button button;
};

struct KeyEvent: public Event {
    enum Key {
        PgUp,
        PgDn,
        Home,
        End,
        Up,
        Down
    };

    Key key;
    bool alt = false;
    bool ctrl = false;
    bool shift = false;
    bool system = false;
};

#endif
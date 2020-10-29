#ifndef EVENTS_H
#define EVENTS_H

namespace Mouse {
    enum Button {
        LeftButton,
        RightButton
    };
}

class Event {
public:
    enum EventType {
        Idle,
        MouseClicked,
        MouseMoved,
        Closed
    };

    EventType type;

    struct MouseClickEvent {
        int x;
        int y;
        Mouse::Button button;
    };

    struct MouseMoveEvent {
        int x;
        int y;
    };

    union {
        MouseClickEvent mouseClick;
        MouseMoveEvent mouseMove;
    };

};

#endif
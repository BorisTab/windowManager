#ifndef EVENTS_H
#define EVENTS_H

//namespace Mouse {
//    enum Button {
//        LeftButton,
//        RightButton
//    };
//}

//class Event {
//public:
//    enum EventType {
//        Idle,
//        MouseClicked,
//        MouseUnclicked,
//        MouseMoved,
//        Closed,
//        ScrollBarCalled
//    };
//
//    EventType type;
//
//    struct MouseClickEvent {
//        int x;
//        int y;
//        Mouse::Button button;
//    };
//
//    struct MouseMoveEvent {
//        int x;
//        int y;
//    };
//
//    struct ScrollBarEvent {
//        int id;
//        int type;
//    };
//
//    union {
//        MouseClickEvent mouseClick;
//        MouseMoveEvent mouseMove;
//        ScrollBarEvent scrollBar;
//    };
//
//};

class Event {
public:
    enum EventType {
        Idle,
        MouseClicked,
        MouseUnclicked,
        MouseMoved,
        Closed,
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
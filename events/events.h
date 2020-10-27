namespace Mouse {
    enum Button {
        LeftButton,
        RightButton
    };
}

class Event {
public:
    enum EventType {
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

    union event{
        MouseClickEvent mouseClick;
        MouseMoveEvent mouseMove;
    };

    union event currentEvent;
};
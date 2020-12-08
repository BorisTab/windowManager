#ifndef EVENTS_H
#define EVENTS_H

#include <vector>
#include <string>
#include "../primitives/colors.h"

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
        ScrollBarAction,
        ScrollGetSliderPos,
        SliderMoved,
        PointerMoved,
        SavePixels,
        UserEvent
    };

    virtual ~Event() = default;

    int type;
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

struct SavePixelsEvent: public Event {
    const std::vector<std::vector<Color>>& pixels;
    const std::string& filePath;

    SavePixelsEvent(const std::vector<std::vector<Color>>& pixels,
                    const std::string& filePath);
};

#endif
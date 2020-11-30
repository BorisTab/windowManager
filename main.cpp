#include <iostream>
#include "application.h"
#include "windows/scrollBar.h"

const Color purple = Color(77, 0, 153);
const Color orange = Color(255, 165, 0);

class ColorChangeButton: public RectButton {
public:
    ColorChangeButton(int x, int y, int width, int height, const Color& color, SystemEventSender* systemEventSender):
        RectButton(x, y, width, height, color, systemEventSender) {}

    void onLeftClick(std::unique_ptr<Event>& event) override {
        color = orange;
    }

    void onLeftUnclick(std::unique_ptr<Event>& event) override {
        color = purple;
    }

    void getEvent(std::unique_ptr<Event> &event) override {
        if (event->type == Event::ScrollBarAction) {
            y = 50 + dynamic_cast<ScrollBarActionEvent*>(event.get())->percent * 200;
            printf("%f\n", dynamic_cast<ScrollBarActionEvent*>(event.get())->percent);
        }

        checkClick(event);

        for (auto window: subWindows) {
            window->getEvent(event);
        }


    }
};

int main() {
    Application app(800, 600, "Engine work");
    app.setBackgroundColor(255, 255, 255);

    ColorChangeButton button(50, 50, 200, 75, purple, app.getSystemEventManager());
    app.addDrawableObject(&button);

    ColorChangeButton button2(50, 400, 200, 75, purple, app.getSystemEventManager());
    app.addDrawableObject(&button2);

    ScrollBar scrollBar(600, 50, 30, 300, app.getSystemEventManager());
    app.addDrawableObject(&scrollBar);

    EventManager::addListener(&scrollBar, &button);

    app.run();

    return 0;
}

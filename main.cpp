#include <iostream>
#include "application.h"

const Color purple = Color(77, 0, 153);
const Color orange = Color(255, 165, 0);

class ColorChangeButton: public RectButton {
public:
    ColorChangeButton(int x, int y, int width, int height, const Color& color):
        RectButton(x, y, width, height, color) {}

    void onLeftClick() override {
        if (color == purple)
            color = orange;
        else
            color = purple;
    }
};

int main() {
    Application app(800, 600, "Engine work");
    app.setBackgroundColor(255, 255, 255);

    ColorChangeButton button(50, 50, 200, 75, purple);
    app.addDrawableObject(&button);
    app.run();

    return 0;
}

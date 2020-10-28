#include <iostream>
#include "application.h"

int main() {
    Application app(800, 600, "Engine work");
    app.setBackgroundColor(255, 255, 255);

    RectangleWindow rectWin(20, 20, 50, 30, Color(77, 0, 153));
    app.addDrawableObject(&rectWin);
    app.run();

    return 0;
}

#include "application.h"

Application::Application(int width, int height, const char* appName):
    engineApp(width, height, appName),
    backgroundColor(0, 0, 0, 255) {
}

void Application::close() {
    appOpen = false;
}

void Application::setBackgroundColor(unsigned char r, unsigned char g, unsigned char b, unsigned char alpha) {
    backgroundColor = Color(r, g, b, alpha);
}

void Application::addDrawableObject(Window *drawableObject) {
    windowsList.push_back(drawableObject);
}

void Application::run() {
    appOpen = true;

    while (appOpen) {
        engineApp.pollEvent(eventQueue);
        while (!eventQueue.empty()) {
            Event event = eventQueue.front();
            eventQueue.pop();

            if (event.type == Event::Closed) {
                close();
            }
        }

        engineApp.clear(backgroundColor);
        for (auto window: windowsList) {
            window->draw(engineApp);
        }

        engineApp.display();
    }

    engineApp.close();
}

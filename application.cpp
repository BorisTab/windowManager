#include "application.h"

Application::Application(int width, int height, const char* appName):
    engineApp(width, height, appName) {}

void Application::close() {
    appOpen = false;
}

void Application::open() {
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

        engineApp.clear();
        engineApp.display();
    }

    engineApp.close();
}

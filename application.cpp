#include "application.h"

std::queue<Event*> EventsQueue::queue;

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

SystemEventSender* Application::getSystemEventManager() {
    return &systemEventSender;
}

void Application::run() {
    appOpen = true;

    while (appOpen) {
        engineApp.pollEvent(EventsQueue::queue);
        while (!EventsQueue::queue.empty()) {
            Event* event = EventsQueue::queue.front();
            EventsQueue::queue.pop();

            if (event->type == Event::Closed) {
                close();
            }

            EventManager::sendEvent(&systemEventSender, *event);
//            delete event;
        }

        engineApp.clear(backgroundColor);
        for (auto window: windowsList) {
            window->draw(engineApp);
        }

        engineApp.display();
    }

    engineApp.close();
}

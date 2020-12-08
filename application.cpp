#include "application.h"
#include <stdio.h>

std::queue<Event*> EventsQueue::queue;

Application::Application(int width, int height, const char* appName):
    engineApp(width, height, appName),
    backgroundColor(0, 0, 0, 255) {}

Application::Application(const char *appName, AppMode appMode):
    backgroundColor(0, 0, 0, 255){
    if (AppMode::fullscreen == appMode) {
        engineApp.setupFullScreenApp(appName);
    } else
        fprintf(stderr, "Error: wrong application mode\n");
}

void Application::close() {
    appOpen = false;
}

void Application::setBackgroundColor(unsigned char r, unsigned char g, unsigned char b, unsigned char alpha) {
    backgroundColor = Color(r, g, b, alpha);
}

void Application::setBackgroundColor(const Color &color) {
    backgroundColor = color;
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
            auto event = std::unique_ptr<Event>(EventsQueue::queue.front());
            EventsQueue::queue.pop();

            if (event->type == Event::Closed) {
                close();
            }

            EventManager::sendEvent(&systemEventSender, event);
        }

        engineApp.clear(backgroundColor);
        for (auto window: windowsList) {
            window->draw(engineApp);
        }

        engineApp.display();
    }

    engineApp.close();
}

void Application::loadImageFromFile(const std::string_view& path, 
                                    const std::string& name) {
    engineApp.addImage(path, name);
}

void Application::loadFontFromFile(const std::string_view& path, 
                                   const std::string& name) {
    engineApp.addFont(path, name);
}

void Application::getEvent(std::unique_ptr<Event>& event) {
    switch (event->type)
    {
    case Event::SavePixels:
        savePixels(event);
        break;
    
    default:
        break;
    }
}

void Application::savePixels(std::unique_ptr<Event>& event) {
    auto savePixelsEvent = dynamic_cast<SavePixelsEvent*>(event.get()); 
    engineApp.savePixels(savePixelsEvent->pixels, 
                         savePixelsEvent->filePath);
}

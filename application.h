#ifndef WINDOWMANAGER_APPLICATION_H
#define WINDOWMANAGER_APPLICATION_H

#include <queue>
#include <list>

#include "config.h"
#include "windows/windows.h"
#include "events/eventQueue.h"
#include "primitives/primitives.h"
#include "windows/sliderPointer.h"

enum AppMode {
    fullscreen
};

class Application: public Window {
private:
    bool appOpen = false;
    Engine engineApp;
    Color backgroundColor;
    std::list<Window*> windowsList;
    SystemEventSender systemEventSender;

public:
    Application(int width, int height, const char* appName);
    Application(const char* appName, AppMode appMode);

    SystemEventSender* getSystemEventManager();
    void setBackgroundColor(unsigned char r, unsigned char g, unsigned char b, unsigned char alpha = 255);
    void setBackgroundColor(const Color& color);
    void close();
    void run();

    void addDrawableObject(Window* drawableObject);

    void loadImageFromFile(const std::string_view& path, 
                           const std::string& name);
    void loadFontFromFile(const std::string_view& path, 
                          const std::string& name);

    void getEvent(std::unique_ptr<Event>& event) override;
    void savePixels(std::unique_ptr<Event>& event);
};

#endif

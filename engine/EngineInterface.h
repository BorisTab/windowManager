#ifndef ENGINE_INTERFACE_H
#define ENGINE_INTERFACE_H

#include "../events/events.h"
#include "../primitives/colors.h"

#include <queue>
#include <string>

class EngineInterface {
public:
    EngineInterface() = default;
    EngineInterface(int width, int height, const char* appName);
protected:
    virtual void drawRect(int x, int y, int width, int height, const Color& color, 
                          const std::string_view& imageName = "") = 0;
    virtual void drawText(int x, int y, const std::string& text, const std::string& fontPath, int fontSize) = 0;

    virtual void setupApp(int width, int height, const char* appName) = 0;
    virtual void clear(const Color& color) = 0;
    virtual void display() = 0;
    virtual void pollEvent(std::queue<Event*>& eventQueue) = 0;
    virtual void close() = 0;
};

#endif
#include "../events/events.h"
#include <queue>

class EngineInterface {
public:
    EngineInterface() = default;
    EngineInterface(int width, int height, const char* appName);
protected:
    virtual void draw() = 0;
    virtual void setupApp(int width, int height, const char* appName) = 0;
    virtual void clear() = 0;
    virtual void display() = 0;
    virtual void pollEvent(std::queue<Event>& eventQueue) = 0;
    virtual void close() = 0;
};

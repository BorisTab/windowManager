#include <queue>
#include "config.h"

class Application {
private:
    bool appOpen = false;
    Engine engineApp;
    std::queue<Event> eventQueue;

public:
    Application(int width, int height, const char* appName);

    void close();
    void open();
};
#include <queue>
#include <list>

#include "config.h"
#include "windows/windows.h"
#include "events/eventQueue.h"

class Application {
private:
    bool appOpen = false;
    Engine engineApp;
    Color backgroundColor;
    std::list<Window*> windowsList;
    SystemEventSender systemEventSender;

public:
    Application(int width, int height, const char* appName);

    SystemEventSender* getSystemEventManager();
    void setBackgroundColor(unsigned char r, unsigned char g, unsigned char b, unsigned char alpha = 255);
    void close();
    void run();

    void addDrawableObject(Window* drawableObject);
};
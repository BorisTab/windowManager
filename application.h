#include <queue>
#include <list>

#include "config.h"
#include "windows/windows.h"

class Application {
private:
    bool appOpen = false;
    Engine engineApp;
    std::queue<Event> eventQueue;
    Color backgroundColor;
    std::list<Window*> windowsList;

public:
    Application(int width, int height, const char* appName);

    void setBackgroundColor(unsigned char r, unsigned char g, unsigned char b, unsigned char alpha = 255);
    void close();
    void run();

    void addDrawableObject(Window* drawableObject);
};
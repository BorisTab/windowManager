#include "../events/events.h"

class BaseObject {
public:
    virtual void pollEvent(Event event) = 0;
};

class RenderWindow: public BaseObject {
private:
    int x = 0;
    int y = 0;
    unsigned int height = 0;
    unsigned int width = 0;

    virtual void draw() = 0;
};
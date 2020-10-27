#include "EngineInterface.h"

#include <SFML/Graphics.hpp>

class SfmlEngine: public EngineInterface {
private:
    sf::RenderWindow window;

public:
    SfmlEngine(int width, int height, const char* appName);
    void draw() override;
    void setupApp(int width, int height, const char* appName) override;
    void clear() override;
    void display() override;
    void pollEvent(std::queue<Event>& eventQueue) override;
    void close() override;

    Event createMouseEvent(sf::Event& engineEvent);
};
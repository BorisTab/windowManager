#ifndef SFML_ENGINE_H
#define SFML_ENGINE_H

#include "EngineInterface.h"

#include <SFML/Graphics.hpp>

class SfmlEngine: public EngineInterface {
private:
    sf::RenderWindow window;

    sf::Color makeSfmlColor(const Color& color);
    MouseEvent* createMouseEvent(sf::Event& engineEvent);
    KeyEvent* createKeyEvent(sf::Event& engineEvent);

public:
    SfmlEngine(int width, int height, const char* appName);
    void drawRect(int x, int y, int width, int height, const Color& color) override;
    void setupApp(int width, int height, const char* appName) override;
    void clear(const Color& color) override;
    void display() override;
    void pollEvent(std::queue<Event*>& eventQueue) override;
    void close() override;
};

#endif
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
    explicit SfmlEngine(const char* appName);
    SfmlEngine() = default;

    void drawRect(int x, int y, int width, int height, const Color& color) override;
    void drawText(int x, int y, const std::string &text, const std::string &fontPath, int fontSize) override;
    void drawPixels(int xStart, int yStart, std::vector<std::vector<Color>>& pixels);

    void setupApp(int width, int height, const char* appName) override;
    void setupFullScreenApp(const char* appName);

    void clear(const Color& color) override;
    void display() override;
    void pollEvent(std::queue<Event*>& eventQueue) override;
    void close() override;

//    static sf::Color makeSfColor(const Color& color);
};

#endif
#ifndef SFML_ENGINE_H
#define SFML_ENGINE_H

#include "EngineInterface.h"

#include <SFML/Graphics.hpp>

class SfmlEngine: public EngineInterface {
private:
    sf::RenderWindow window;
    std::map<std::string, sf::Texture> imageMap;
    std::map<std::string, sf::Font> fontMap;

    sf::Color makeSfmlColor(const Color& color);
    MouseEvent* createMouseEvent(sf::Event& engineEvent);
    KeyEvent* createKeyEvent(sf::Event& engineEvent);

public:
    SfmlEngine(int width, int height, const char* appName);
    explicit SfmlEngine(const char* appName);
    SfmlEngine() = default;

    void drawRect(int x, int y, int width, int height, const Color& color,
                  const std::string_view& imageName = "") override;
    void drawText(int x, int y, const std::string &text, 
                  const std::string &font, 
                  int fontSize, 
                  const Color& color) override;
    void drawPixels(int xStart, int yStart, std::vector<std::vector<Color>>& pixels);

    void setupApp(int width, int height, const char* appName) override;
    void setupFullScreenApp(const char* appName);

    void clear(const Color& color) override;
    void display() override;
    void pollEvent(std::queue<Event*>& eventQueue) override;
    void close() override;

    void addImage(const std::string_view& path, 
                  const std::string& name);
    void addFont(const std::string_view& path, 
                 const std::string& name);

    void savePixels(const std::vector<std::vector<Color>>& pixels,
                    const std::string& filePath);
};

#endif
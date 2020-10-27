#include "SfmlEngine.h"

SfmlEngine::SfmlEngine(int width, int height, const char *appName): EngineInterface(width, height, appName),
    window(sf::RenderWindow(sf::VideoMode(width, height), appName)) {}

void SfmlEngine::setupApp(int width, int height, const char *appName) {
    window.create(sf::VideoMode(width, height), appName);
}

void SfmlEngine::clear() {
    window.clear();
}

void SfmlEngine::display() {
    window.display();
}

void SfmlEngine::draw() {

}
void SfmlEngine::close() {
    window.close();
}

Event SfmlEngine::createMouseEvent(sf::Event& engineEvent) {
    Event event;

    event.type = Event::MouseClicked;
    event.currentEvent.mouseClick.x = engineEvent.mouseButton.x;
    event.currentEvent.mouseClick.y = engineEvent.mouseButton.y;

    switch (engineEvent.mouseButton.button) {
        case sf::Mouse::Left:
            event.currentEvent.mouseClick.button = Mouse::LeftButton;

        case sf::Mouse::Right:
            event.currentEvent.mouseClick.button = Mouse::RightButton;

        default:
            break;
    }

    return event;
}

void SfmlEngine::pollEvent(std::queue<Event>& eventQueue) {
    sf::Event engineEvent;
    while (window.pollEvent(engineEvent)) {
        Event event;

        switch (engineEvent.type) {
            case sf::Event::EventType::Closed:
                event.type = Event::Closed;
                break;

            case sf::Event::EventType::MouseButtonPressed:
                event = createMouseEvent(engineEvent);

            default:
                break;
        }
        eventQueue.push(event);
    }
}

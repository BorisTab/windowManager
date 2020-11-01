#include "SfmlEngine.h"

SfmlEngine::SfmlEngine(int width, int height, const char *appName):
    EngineInterface(width, height, appName),
    window(sf::RenderWindow(sf::VideoMode(width, height), appName)) {}

void SfmlEngine::setupApp(int width, int height, const char *appName) {
    window.create(sf::VideoMode(width, height), appName);
}

sf::Color SfmlEngine::makeSfmlColor(const Color &color) {
    return sf::Color(color.r, color.g, color.b, color.alpha);
}

void SfmlEngine::clear(const Color& color) {
    window.clear(makeSfmlColor(color));
}

void SfmlEngine::display() {
    window.display();
}

void SfmlEngine::drawRect(int x, int y, int width, int height, const Color& color) {
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(width, height));
    rect.setPosition(x, y);
    rect.setFillColor(makeSfmlColor(color));

    window.draw(rect);
}

void SfmlEngine::close() {
    window.close();
}

MouseEvent* SfmlEngine::createMouseEvent(sf::Event& engineEvent) {
    auto event = new MouseEvent;

    if (engineEvent.type == sf::Event::MouseMoved) {
        event->x = engineEvent.mouseMove.x;
        event->y = engineEvent.mouseMove.y;

        event->type = Event::MouseMoved;
        return event;
    }

    event->x = engineEvent.mouseButton.x;
    event->y = engineEvent.mouseButton.y;

    if (engineEvent.type == sf::Event::MouseButtonPressed)
        event->type = Event::MouseClicked;
    else if (engineEvent.type == sf::Event::MouseButtonReleased)
        event->type = Event::MouseUnclicked;

    switch (engineEvent.mouseButton.button) {
        case sf::Mouse::Left:
            event->button = MouseEvent::LeftButton;
            break;

        case sf::Mouse::Right:
            event->button = MouseEvent::RightButton;
            break;

        default:
            break;
    }

    return event;
}

KeyEvent* SfmlEngine::createKeyEvent(sf::Event &engineEvent) {
    auto event = new KeyEvent;
    event->type = Event::KeyClicked;

    event->alt = engineEvent.key.alt;
    event->ctrl = engineEvent.key.control;
    event->shift = engineEvent.key.shift;
    event->system = engineEvent.key.system;

    switch (engineEvent.key.code) {
        case sf::Keyboard::PageUp:
            event->key = KeyEvent::PgUp;
            break;

        case sf::Keyboard::PageDown:
            event->key = KeyEvent::PgDn;
            break;

        case sf::Keyboard::Home:
            event->key = KeyEvent::Home;
            break;

        case sf::Keyboard::End:
            event->key = KeyEvent::End;
            break;

        case sf::Keyboard::Up:
            event->key = KeyEvent::Up;
            break;

        case sf::Keyboard::Down:
            event->key = KeyEvent::Down;
            break;

        default:
            break;
    }

    return event;
}

void SfmlEngine::pollEvent(std::queue<Event*>& eventQueue) {
    sf::Event engineEvent = {};
    while (window.pollEvent(engineEvent)) {
        Event *event = nullptr;

        switch (engineEvent.type) {
            case sf::Event::Closed:
                event = new Event;
                event->type = Event::Closed;
                eventQueue.push(event);
                break;

            case sf::Event::MouseButtonPressed:
            case sf::Event::MouseButtonReleased:
            case sf::Event::MouseMoved:
                event = createMouseEvent(engineEvent);
                eventQueue.push(event);
                break;

            case sf::Event::KeyPressed:
                event = createKeyEvent(engineEvent);
                eventQueue.push(event);
                break;

            default:
                break;
        }
    }
}

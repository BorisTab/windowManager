#ifndef BASE_OBJECTS_H
#define BASE_OBJECTS_H

#include "baseWindow.h"
#include "../events/eventManager.h"

class RectangleWindow: public Window {
public:
    int x = 0;
    int y = 0;
    int height = 0;
    int width = 0;
    std::string imageName;
    Color color;

public:
    RectangleWindow(int x, int y, int width, int height, const Color& color);
    RectangleWindow(int x, int y, int width, int height, const Color& color, 
                    const std::string& imageName);
    void draw(Engine& engine) override;
};

class RectButton: public RectangleWindow {
private:

public:
    RectButton(int x, int y, int width, int height, const Color& color, 
               SystemEventSender* systemEventSender, 
               const std::string& imageName = "");

    virtual void onLeftClick(std::unique_ptr<Event>& event) = 0;
    virtual void onLeftUnclick(std::unique_ptr<Event>& event) = 0;
    void getEvent(std::unique_ptr<Event>& event) override;
    void checkClick(std::unique_ptr<Event>& event);
};

class RectMoveable: public RectButton {
protected:
    bool mousePressed = false;

public:
    RectMoveable(int x, int y, int width, int height, 
                 const Color& color, 
                 SystemEventSender* systemEventSender, 
                 const std::string& imageName = "");

    void getEvent(std::unique_ptr<Event>& event) override;
    void onLeftClick(std::unique_ptr<Event>& event) override;
    void onLeftUnclick(std::unique_ptr<Event>& event) override;

    virtual void onMouseMove(std::unique_ptr<Event>& event) = 0;
};

class RectPixelButton: public RectButton {
protected:
    std::vector<std::vector<Color>> pixels;

public:
    RectPixelButton(int x, int y, int width, int height, 
                    const Color& color, 
                    SystemEventSender* systemEventSender);

    std::vector<std::vector<Color>>& getPixels();
    void setPixels(uint32_t* newPixels, int width, int height);

    void draw(Engine& engine) override;
};

class Text: public Window {
private:
    int x = 0;
    int y = 0;
    int fontSize = 18;
    std::string text;
    std::string font;
    Color color;
public:
    Text(int x, int y, const std::string& text, 
         const std::string& fontName,
         int fontSize, 
         const Color& color);

    void setFont(const std::string& fontName);
    void setFontSize(int size);

    void draw(Engine &engine) override;
};

#endif

#ifndef SLIDERPOINTER_WINDOWMANAGER_H
#define SLIDERPOINTER_WINDOWMANAGER_H

#include "windows.h"
#include "../primitives/primitives.h"

class Slider: public RectMoveable {
private:
    bool vertical;
protected:
    double value;
    double minPos;
    double maxPos;

public:
    Slider(int x, int y, int width, int height,
           const Color& color, 
           SystemEventSender* systemEventSender, 
           int minPos, int maxPos, 
           bool vertical = false);
    
    void onMouseMove(std::unique_ptr<Event>& event) override;
    void onLeftClick(std::unique_ptr<Event>& event) override;
    
    double insideCheck(double pos);
    void sendMoveEvent();
};

class Pointer: public RectMoveable {
private:
    double xValue;
    double yValue;

    double minX;
    double maxX;
    double minY;
    double maxY;

public:
    Pointer(int x, int y, int width, int height,
           const Color& color, 
           SystemEventSender* systemEventSender, 
           int minX, int maxX, 
           int minY, int maxY);
    
    void onMouseMove(std::unique_ptr<Event>& event) override;
    void onLeftClick(std::unique_ptr<Event>& event) override;
    
    Point insideCheck(double x, double y);
    void sendMoveEvent();
};

struct SliderMoveEvent: public Event {
    double xValue = 0;
    double yValue = 0;

    SliderMoveEvent();
};

struct PointerMoveEvent: public Event {
    double xValue = 0;
    double yValue = 0;

    PointerMoveEvent();
};

#endif
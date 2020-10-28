#ifndef GLUT_ENGINE_H
#define GLUT_ENGINE_H

#include "EngineInterface.h"

#include <GL/freeglut.h>

class GlutEngine: public EngineInterface {
private:
    int window = 0;
    static std::queue<Event> engineEventQueue;
public:
    GlutEngine(int width, int height, const char* appName);

    void drawRect(int x, int y, int width, int height, const Color& color) override;
    void setupApp(int width, int height, const char* appName) override;
    void clear(const Color& color) override;
    void display() override;
    void pollEvent(std::queue<Event>& eventQueue) override;
    void close() override;

    static void renderCanvas();
    static void addCloseEvent();
};

#endif
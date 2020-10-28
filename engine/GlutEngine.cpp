#include "GlutEngine.h"

std::queue<Event> GlutEngine::engineEventQueue = {};

GlutEngine::GlutEngine(int width, int height, const char *appName):
    EngineInterface(width, height, appName) {

    int pargc = 0;
    glutInit(&pargc, nullptr);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(width, height);
    window = glutCreateWindow(appName);

    glutDisplayFunc(renderCanvas);
    glutCloseFunc(addCloseEvent);
}

void GlutEngine::draw() {

}

void GlutEngine::close() {}

void GlutEngine::pollEvent(std::queue<Event> &eventQueue) {
    if (eventQueue.empty()) {
        eventQueue = std::move(engineEventQueue);
        engineEventQueue = std::queue<Event>();
        return;
    }

    while (!engineEventQueue.empty()) {
        eventQueue.push(engineEventQueue.front());
        engineEventQueue.pop();
    }
}

void GlutEngine::setupApp(int width, int height, const char *appName) {
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);
    window = glutCreateWindow(appName);

    glutDisplayFunc(renderCanvas);
    glutCloseFunc(addCloseEvent);
}

void GlutEngine::clear(const Color& color) {
    glClearColor(color.r, color.g, color.b, color.alpha);
}

void GlutEngine::display() {
    glutMainLoopEvent();
}

void GlutEngine::renderCanvas() {
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

void GlutEngine::addCloseEvent() {
    Event event = {};
    event.type = Event::Closed;
    engineEventQueue.push(event);
}



#include "GlutEngine.h"

std::queue<Event*> GlutEngine::engineEventQueue = {};

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

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0, width, height, 0, 0, 1 );

//    glMatrixMode( GL_MODELVIEW );
//    glLoadIdentity();
}

// void GlutEngine::drawRect(int x, int y, int width, int height, const Color& color) {
//    glColor4i(color.r, color.g, color.b, color.alpha);
//    glRecti(x, y, x + width, x + height);

//     glPushMatrix();
//     glColor3f(1.0f,0.0f,0.0f);
//     glRectf(10,10,150,100);
//     glPopMatrix();
// }

void GlutEngine::drawText(int x, int y, const std::string &text, 
                          const std::string &fontPath, 
                          int fontSize, 
                          const Color& color) {

}

void GlutEngine::close() {}

void GlutEngine::pollEvent(std::queue<Event*> &eventQueue) {
    if (eventQueue.empty()) {
        eventQueue = std::move(engineEventQueue);
        engineEventQueue = std::queue<Event*>();
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
    glClearColor(color.r / 255.0, color.g / 255.0, color.b / 255.0, color.alpha / 255.0);
}

void GlutEngine::display() {
    glutMainLoopEvent();
}

void GlutEngine::renderCanvas() {
    glClear(GL_COLOR_BUFFER_BIT);
//    glPushMatrix();

//    glColor3f(1.0f,0.0f,0.0f);
//    glRectf(10,10,150,100);

//    glPopMatrix();
    glutSwapBuffers();
}

void GlutEngine::addCloseEvent() {
    Event event = {};
    event.type = Event::Closed;
    engineEventQueue.push(&event);
}



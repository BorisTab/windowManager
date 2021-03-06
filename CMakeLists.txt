cmake_minimum_required(VERSION 3.18)
project(windowManager)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "-pthread")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

add_library(windowManager STATIC 
            engine/EngineInterface.h engine/EngineInterface.cpp 
            config.h 
            events/events.cpp events/events.h 
            application.cpp application.h 
            windows/windows.cpp windows/windows.h 
            engine/SfmlEngine.cpp engine/SfmlEngine.h 
            engine/GlutEngine.cpp engine/GlutEngine.h 
            primitives/vector3.h 
            primitives/colors.h 
            events/eventQueue.h 
            windows/scrollBar.cpp windows/scrollBar.h 
            windows/baseWindow.cpp windows/baseWindow.h 
            events/eventManager.cpp events/eventManager.h 
            windows/viewPort.cpp windows/viewPort.h 
            primitives/primitives.cpp primitives/primitives.h
            windows/sliderPointer.cpp windows/sliderPointer.h)

target_link_libraries(windowManager sfml-graphics sfml-audio ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

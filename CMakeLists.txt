cmake_minimum_required(VERSION 3.18)
project(windowManager)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "-pthread")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(windowManager main.cpp engine/EngineInterface.h engine/EngineInterface.cpp config.h events/events.cpp events/events.h application.cpp application.h baseObjects/baseObjects.cpp baseObjects/baseObjects.h engine/SfmlEngine.cpp engine/SfmlEngine.h)

target_link_libraries(windowManager sfml-graphics sfml-audio)

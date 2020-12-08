#include "events.h"

SavePixelsEvent::SavePixelsEvent(const std::vector<std::vector<Color>>& pixels,
                                 const std::string& filePath):
    pixels(pixels),
    filePath(filePath) {
    type = Event::SavePixels;
}
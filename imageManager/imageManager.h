#ifndef IMAGEMANAGER_WINDOWMANAGER_H
#define IMAGEMANAGER_WINDOWMANAGER_H

#include <string>

class ImageManager {
public:
    static void loadImageFromFile(const std::string_view& path, 
                                  const std::string_view& name);
};

#endif
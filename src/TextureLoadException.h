#ifndef TEXTURE_LOAD
#define TEXTURE_LOAD

#include <stdexcept>
#include <string>

class TextureLoadException: public std::runtime_error
{
public:
    explicit TextureLoadException(const std::string &path)
        : std::runtime_error("Failed to load texture: " + path) {}
};
#endif
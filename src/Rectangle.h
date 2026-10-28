#include <cstdint>

class Rectangle
{
private:
    int16_t x;
    int16_t y;
    int16_t width;
    int16_t height;

public:
    Rectangle(int16_t x, int16_t y, int16_t w, int16_t h);
    ~Rectangle();
};
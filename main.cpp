
#include "Maths/vec3.h"
#include "Utility/color.h"

#include <iostream>

int main()
{
    const int16_t img_width = 256;
    const int16_t img_height = 256;

    std::cout << "P3\n" << img_width << ' ' << img_height << "\n255\n";

    for(int16_t y = 0; y < img_height; ++y)
    {
        for(int16_t x = 0; x < img_width; ++x)
        {
            auto r = double(x) / (img_width -1);
            auto g = double(y) / (img_height -1);
            auto b = 0;
            auto pixelColor = color(r, g, b);
            Write_Color(std::cout, pixelColor);
        }
    }
}
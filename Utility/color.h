#pragma once

#include "Maths/vec3.h"
#include <iostream>

using Color = Vec3;

void Write_Color(std::ostream& out, const Color& pixel_color)
{
    out << static_cast<int>(255.999 * pixel_color.X) << ' '
        << static_cast<int>(255.999 * pixel_color.Y) << ' '
        << static_cast<int>(255.999 * pixel_color.Z) << '\n';
}
#pragma once

#include "Maths/vec3.h"


class Ray
{
public:

    Ray() {}
    Ray(const Point3& InOrigin, const Vec3& InDirection)
    : Origin(InOrigin), Direction(InDirection)
    {}

    Point3 At(double t) const
    {
        return Origin + t * Direction;
    }

    const Point3& GetOrigin() const { return Origin; }
    const Vec3& GetDirection() const { return Direction; }
private:
    Point3 Origin;
    Vec3 Direction;
};
#pragma once

#include <cmath>
#include <iostream>

class vec3
{
public:
    double X;
    double Y;
    double Z;

    vec3() : X(0), Y(0), Z(0) {}
    vec3(double x, double y, double z) : X(x), Y(y), Z(z) {}

    vec3 operator-() const { return vec3(-X, -Y, -Z); }
    double operator[](int i) const { return i == 0 ? X : (i == 1 ? Y : Z); }
    double& operator[](int i) { return i == 0 ? X : (i == 1 ? Y : Z); }

    vec3& operator+=(const vec3& v)
    {
        X += v.X;
        Y += v.Y;
        Z += v.Z;
        return *this;
    }

    vec3& operator*=(const double t)
    {
        X *= t;
        Y *= t;
        Z *= t;
        return *this;
    }

    vec3& operator/=(const double t)
    {
        return *this *= 1 / t;
    }

    double Length() const
    {
        return std::sqrt(Length_squared());
    }

    double Length_squared() const
    {
        return X * X + Y * Y + Z * Z;
    }

};

// Type aliase to distinguish between points and vectors
using point3 = vec3;

// vec3 Utility Functions
inline std::ostream& operator<<(std::ostream& out, const vec3& v)
{
    return out << v.X << ' ' << v.Y << ' ' << v.Z;
}

inline vec3 operator+(const vec3& u, const vec3& v)
{
    return vec3(u.X + v.X, u.Y + v.Y, u.Z + v.Z);
}

inline vec3 operator-(const vec3& u, const vec3& v)
{
    return vec3(u.X - v.X, u.Y - v.Y, u.Z - v.Z);
}

inline vec3 operator*(const vec3& u, const vec3& v)
{
    return vec3(u.X * v.X, u.Y * v.Y, u.Z * v.Z);
}

inline vec3 operator*(double t, const vec3& v)
{
    return vec3(t * v.X, t * v.Y, t * v.Z);
}

inline vec3 operator*(const vec3& v, double t)
{
    return t * v;
}

inline vec3 operator/(vec3 v, double t)
{
    return (1 / t) * v;
}

inline double Dot(const vec3& u, const vec3& v)
{
    return u.X * v.X + u.Y * v.Y + u.Z * v.Z;
}

inline vec3 Cross(const vec3& u, const vec3& v)
{
    return vec3(u.Y * v.Z - u.Z * v.Y,
                u.Z * v.X - u.X * v.Z,
                u.X * v.Y - u.Y * v.X);
}

inline vec3 Unit_vector(vec3 v)
{
    return v / (Dot(v,v) / v.Length_squared() );
}
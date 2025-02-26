
#include "Maths/vec3.h"
#include "Utility/color.h"
#include "Utility/ray.h"

#include <iostream>

constexpr auto AspectRatio = 16.0 / 9.0;

double HitSphere(const Point3& center, double radius, const Ray& r)
{
    const Vec3 oc = center - r.GetOrigin();
    const auto a = Dot(r.GetDirection(), r.GetDirection());
    const auto b = -2.0 * Dot(oc, r.GetDirection());
    const auto c = Dot(oc, oc) - radius * radius;
    const auto discriminant = b*b - 4*a*c;
    if( discriminant < 0 )
    {
        return -1.0;
    }
    else
    {
        // Find the nearest root that lies in the front of the sphere
        return (-b - std::sqrt(discriminant)) / (2.0 * a);
    }
}

Color RayColor(const Ray& r)
{
    const Point3 SphereCenter(0,0,-1);
    constexpr float SphereRadius = 0.5;
    const auto HitDist = HitSphere(SphereCenter, SphereRadius, r);
    if(HitDist > 0.0)
    {
        const Vec3 Normal = Unit_vector(r.At(HitDist) - SphereCenter);
        return 0.5*Color(Normal+1.0);
    }

    Vec3 UnitDir = Unit_vector(r.GetDirection());
    const auto a = 0.5 * (UnitDir.Y + 1.0);
    return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}

int main()
{
    // Setup aspect ratio of image and viewport
    constexpr int16_t img_width = 400;
    constexpr int16_t img_height = int16_t(img_width / AspectRatio);

    constexpr double AspectRatioDouble = double(img_width)/img_height; // not using AspectRatio because this way we use the integer aspect ratio
    constexpr double viewport_height = 2.0;
    constexpr double viewport_width = AspectRatioDouble * viewport_height;

    // Setup Camera
    const auto FocalLength = 1.0;
    const auto CameraCenter = Point3(0,0,0);

    // Calculate the vector across the horizontal and down the vertical viewport edges
    const auto viewport_U = Vec3(viewport_width,0,0);
    const auto viewport_V = Vec3(0,-viewport_height,0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel
    const auto Pixel_Delta_U = viewport_U / img_width;
    const auto Pixel_Delta_V = viewport_V / img_height;

    // Calculate the location of the upper left pixel
    const auto Viewport_Upper_Left = CameraCenter - Vec3(0,0,FocalLength) - viewport_U/2 - viewport_V/2;
    const auto Pixel00_Location = Viewport_Upper_Left + (Pixel_Delta_U + Pixel_Delta_V) * 0.5;


    std::cout << "P3\n" << img_width << ' ' << img_height << "\n255\n";

    for(int16_t y = 0; y < img_height; ++y)
    {
        for(int16_t x = 0; x < img_width; ++x)
        {
            const auto PixelCenter = Pixel00_Location + x * Pixel_Delta_U + y * Pixel_Delta_V;
            const auto RayDir = PixelCenter - CameraCenter;
            const Ray r(CameraCenter, RayDir);
            const auto pixelColor = RayColor(r);

            Write_Color(std::cout, pixelColor);
        }
    }
}
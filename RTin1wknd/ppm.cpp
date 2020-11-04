/*
 * =====================================================================================
 *
 *       Filename:  ppm.cpp
 *
 *    Description: Ray Tracing in One Weekend. 
 *
 *        Version:  1.0
 *        Created:  08/29/20 10:04:52
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Richard I. Christopher 
 *   Organization:  Brand Media
 *
 * =====================================================================================
 */

#include <iostream>
#include <algorithm>
#include "ray.h"

double spherical(const vec3 &center, double radius, const ray &ray){
    vec3 originOffest = ray.origin() - center;
    double a = ray.direction().sqrLength();
    double halfb = Dot(originOffest, ray.direction());
    double c = originOffest.sqrLength() - (radius * radius);
    double discriminant = (halfb * halfb) - (a * c);
    if (discriminant < 0){
        return -1.0;
    } else {
        return (-halfb - sqrt(discriminant)) / a ;
    }
}

vec3 reflection (const ray &r){
    double t = spherical(vec3(0.0, 0.0, -4.5), 0.5, r);
    if(t > 0.0){
        vec3 normal = Unit(r.pointParam(t) - vec3(0.0, 0.0, -4.5));
        return 0.5 * vec3(normal.x() + 1, normal.y() + 1, normal.z() + 1);
    }
    vec3 unitDirection = Unit(r.direction()); 
    t = 0.5 * (unitDirection.y() + 1.0); // translates y from (-1-1) to (0-1)
    return ((1-t) * vec3(0.2,0.1,0.1)) + (t * vec3(0.05, 0.0, 0.1)); // lerp 1-t*start + t*end
}

void draw(std::ostream &out, vec3 colors);

int main(){

    // Image Dimensions
    const auto aspect = 16.0/9.0;
    const int ix = 1000;
    const int jy = static_cast<int>(ix / aspect);

    // Camera
    auto fovY = 16.0;
    auto fovX = fovY * aspect;
    auto focZ = 18.0;

    auto origin = vec3(0.0, 0.0, 0.0);
    auto horizontal = vec3(fovX, 0, 0);
    auto vertical = vec3(0, fovY, 0);
    auto depth = vec3(0, 0, focZ);
    auto bottomLeft = origin - horizontal/2 - vertical/2 - depth;

    // Render Image
    std::cout << "P3\n" << ix << ' ' << jy << "\n255\n";

    for (int j = jy-1; j >= 0; --j){
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < ix; i++){
            double u = double(i) / (ix - 1);
            double v = double(j) / (jy - 1);

            ray r(origin, bottomLeft + (u * horizontal) + (v * vertical) - origin);
            vec3 color = reflection(r);
            color *= 256;
            draw(std::cout, Clamp(color, 256, 0));
            // draw(std::cout, color);
        }
    }
    std::cerr << "\nDone.\n";
}

// writes translated [0,255] color components
void draw(std::ostream &out, vec3 colors){
    out << colors.x() << ' ' 
        << colors.y() << ' ' 
        << colors.z() << '\n';
}

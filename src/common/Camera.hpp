#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include "Vec3.hpp"
#include "Ray.hpp"

class Camera {
    public:
        Camera() {
            aspect_ratio = 16.0 / 9.0;
            viewport_width = 460;
            viewport_height = static_cast<int>(viewport_width / aspect_ratio);
            origin = Point3(0.0, 0.0, 0.0);

            lower_left_corner = origin - horizontal/2 - vertical/2 - Vec3d(0, 0, focal_length);
            horizontal = Vec3d(viewport_width, 0, 0);
            vertical = Vec3d(0, viewport_height, 0);
        }

        Ray compute_ray(double u, double v) {
            return Ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
        }

    private:

        Point3 origin;
        int viewport_height = 0;
        int viewport_width = 0;
        double focal_length = 1.0;
        double aspect_ratio = 0;


        Point3 lower_left_corner;
        Point3 horizontal;
        Point3 vertical;

};

#endif
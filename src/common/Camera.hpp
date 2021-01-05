#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include "Vec3.hpp"
#include "Ray.hpp"

class Camera {
    public:
        Camera(int width, int height) {
            
            _origin = Point3(0.0, 0.0, 0.0);
            _image_width = width;
            _image_height = height;
            double aspect_ratio = width/static_cast<double>(height);

            _viewport_height = 2.0;
            _viewport_width = _viewport_height * aspect_ratio;

            _horizontal = Vec3d(_viewport_width, 0, 0);
            _vertical = Vec3d(0, _viewport_height, 0);
            _lower_left_corner = _origin - _horizontal/2 - _vertical/2 - Vec3d(0, 0, _focal_length);
            
        }

        int image_height() const {
            return _image_height;
        }
        int image_width() const {
            return _image_width;
        }

        Ray compute_ray(double u, double v) {
            return Ray(_origin, _lower_left_corner + u*_horizontal + v*_vertical - _origin);
        }

    private:

        Point3 _origin;
        int _image_width = 0;
        int _image_height = 0;
        double _viewport_height = 0;
        double _viewport_width = 0;
        double _focal_length = 1.0;


        Point3 _lower_left_corner;
        Point3 _horizontal;
        Point3 _vertical;

};

#endif
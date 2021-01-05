#ifndef __RAY_HPP__
#define __RAY_HPP__

#include "Vec3.hpp"

class Ray {
    public:

        Ray() {}
        Ray(const Point3& orig, const Vec3d& dir) : orig(orig), dir(dir) {}
        Point3 origin() { return orig; }
        Vec3d direction() { return dir; }

        Point3 at(double t) {
            return orig + dir*t;
        }

    protected:

        Point3 orig;
        Vec3d dir;
};

#endif
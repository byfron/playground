#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__
#include <common/Vec3.hpp>
#include <common/Ray.hpp>

struct HitRecord {
    Point3 p;
    Vec3d normal;
    double t;
    bool front_face;

    inline void set_face_normal(const Ray& r, const Vec3d& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal :-outward_normal;
    }
};

class Object {
    public:
        virtual bool hit(const Ray& ray, double t_min, double t_max, HitRecord& record) const = 0;
};

#endif
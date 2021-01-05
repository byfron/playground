#ifndef __SPHERE_HPP__
#define __SPHERE_HPP__

#include "Object.hpp"
#include <common/Ray.hpp>
#include <common/Vec3.hpp>

class Sphere : public Object {
    public:

    Sphere(const Vec3d& c, double r) : center(c), radius(r) {}

    virtual bool hit(const Ray& ray, double t_min, double t_max, HitRecord& record) const override {
        Vec3d oc = ray.origin() - center;
        auto a = dot(ray.direction(), ray.direction());
        auto half_b = dot(oc, ray.direction());
        auto c = oc.length_squared() - radius*radius;
        auto discriminant = half_b*half_b - a*c; //sqrt of the quadratic formula
        if (discriminant < 0) return false;

        // Find the nearest root that lies in the acceptable range.
        auto sqrtd = sqrt(discriminant);
        auto root = (-half_b - sqrtd) / a; //smaller root should be the intersection closest to the camera
        if (root < t_min || t_max < root) {
            root = (-half_b + sqrtd) / a;
            if (root < t_min || t_max < root)
                return false;
        }

        record.t = root;
        record.p = ray.at(record.t);
        auto outward_normal = (record.p - center) / radius;
        record.set_face_normal(ray, outward_normal);

        return true;
    }

    private:

    Vec3d center;
    double radius = 0;
};

#endif
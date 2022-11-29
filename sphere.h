//
// Created by Thierry Backes on 26.11.22.
//

#ifndef REETRACER_SPHERE_H
#define REETRACER_SPHERE_H
#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
public:
    sphere() = default;
    sphere(point3 cen, double r, shared_ptr<material> m): center(cen), radius(r), mat_ptr(m) {};

    bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

public:
    point3 center;
    double radius;
    shared_ptr<material> mat_ptr;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    rec.t = 0;
    rec.p = r.at(rec.t);
    rec.mat_ptr = mat_ptr;
    rec.set_face_normal(r, vec3(0, 0, 0));

    return true;
}
#endif //REETRACER_SPHERE_H

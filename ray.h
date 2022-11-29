//
// Created by Thierry Backes on 24.11.22.
//

#ifndef REETRACER_RAY_H
#define REETRACER_RAY_H

#include "vec3.h"

class ray {
public:
    ray() = default;
    ray(const point3& origin, const vec3& direction)
            : orig(origin), dir(direction)
    {}

    [[nodiscard]] point3 origin() const  { return orig; }
    [[nodiscard]] vec3 direction() const { return dir; }

    [[nodiscard]] point3 at(double t) const {
        return orig + t*dir;
    }

public:
    point3 orig;
    vec3 dir;
};


#endif //REETRACER_RAY_H

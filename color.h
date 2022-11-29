//
// Created by Thierry Backes on 24.11.22.
//

#ifndef REETRACER_COLOR_H
#define REETRACER_COLOR_H

#include "vec3.h"

#include <iostream>

void write_color(std::ostream &out, color pixel_color, int samples_per_pixel) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Divide the color by the number of samples.
    auto scale = 1.0 / samples_per_pixel;
    r = sqrt(scale *r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(255 * clamp(r, 0.0, 1.0)) << ' '
        << static_cast<int>(255 * clamp(g, 0.0, 1.0)) << ' '
        << static_cast<int>(255 * clamp(b, 0.0, 1.0)) << '\n';
}

#endif //REETRACER_COLOR_H

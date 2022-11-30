#include "rtweekend.h"

#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

#include <iostream>
#include <fstream>

color ray_color(const ray& r,  const color &background, const hittable& world) {
    hit_record rec;

    if (!world.hit(r, 0, infinity, rec))
        return background;

    ray scattered;
    color attenuation;
    color emitted = rec.mat_ptr->emitted();

    if(!rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        return emitted;

    return emitted + attenuation;
}

hittable_list generate_scene() {
    hittable_list world;

    auto material_center = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_ground = make_shared<diffuse_light>(color(0.8, 0.8, 0.8));
    auto material_left   = make_shared<dielectric>(1.5);
    auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);

    world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.0),   0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0), -0.45, material_left));
    world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));

    return world;
}

int main() {
    size_t num_threads = 1;

    // Image
    const auto aspect_ratio = 3.0 / 2.0;
    const int image_width = 600;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 64;
    assert(samples_per_pixel%num_threads == 0);

    // World
    color background(0,0,0);
    auto world = generate_scene();

    // Camera
    point3 lookfrom(0,0,3);
    point3 lookat(0,0,-1);
    vec3 vup(0,1,0);
    camera cam(lookfrom, lookat, vup, 20, aspect_ratio);

    // Render
    std::ofstream ofs;
    ofs.open("out.ppm", std::ofstream::out);

    ofs << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            color pixel_color(0, 0, 0);

            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + random_double()) / (image_width-1);
                auto v = (j + random_double()) / (image_height-1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, background, world);
            }

            write_color(ofs, pixel_color, samples_per_pixel);
        }
    }
    std::cerr << "\nDone.\n";

    return 0;
}

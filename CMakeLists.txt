cmake_minimum_required(VERSION 3.16)
project(reetracer)

set(CMAKE_CXX_STANDARD 17)

add_executable(reetracer main.cpp vec3.h color.h ray.h hittable.h sphere.h hittable_list.h rtweekend.h camera.h material.h)

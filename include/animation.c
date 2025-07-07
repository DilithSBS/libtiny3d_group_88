/*
    All the functions related to animating objects are implemented here
    vec3_bezier()
*/

#include "../include/animation.h"

// besier points are created to make a smooth bezier curve
vec3_t vec3_bezier(vec3_t p0, vec3_t p1, vec3_t p2, vec3_t p3, float t) {
    float u = 1 - t;
    vec3_t a = vec3_scale(p0, u * u * u);
    vec3_t b = vec3_scale(p1, 3 * u * u * t);
    vec3_t c = vec3_scale(p2, 3 * u * t * t);
    vec3_t d = vec3_scale(p3, t * t * t);
    return vec3_add(vec3_add(a, b), vec3_add(c, d));
}

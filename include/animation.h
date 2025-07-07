/*
    All the functions related to animating objects are included here
    vec3_bezier()
*/

#ifndef ANIMATION_H
#define ANIMATION_H

#include "math3d.h"

// besier points are created to make a smooth bezier curve
vec3_t vec3_bezier(vec3_t p0, vec3_t p1, vec3_t p2, vec3_t p3, float t);

#endif // ANIMATION_H

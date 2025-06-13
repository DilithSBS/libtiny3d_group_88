#ifndef MATH3D_H
#define MATH3D_H

#include <stdio.h>
#include <math.h>

typedef struct {
    double x, y, z;
    double r, theta, phi;
} vec3_t;

// Automatically update spherical coordinates by cartesian coordinates
void updateSph(vec3_t *v);
// Automatically update cartesian coordinates by spherical coordinates
void updateCar(vec3_t *v)

// Update cartesian coordinates by spherical coordinates
//vec3_t vec3_from_spherical (double r, double theta, double phi);

#endif
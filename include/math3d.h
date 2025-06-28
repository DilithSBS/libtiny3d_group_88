#ifndef MATH3D_H
#define MATH3D_H

#include <stdio.h>
#include <math.h>

// ------------------ Vector Structures ------------------

// Store 3D vectors
typedef struct {
    double x, y, z;         // As cartesian coordinates
    double r, theta, phi;   // As spherical coordinates
} vec3_t;

typedef struct {
    float x, y, z, w;
} vec4_t;

// ------------------ Matrix Structure ------------------

typedef struct {
    float element[16]; // Column-major 4x4 matrix
} mat4;

// ------------------ Matrix Functions ------------------

mat4 mat4_identity();
mat4 mat4_translate(float tx, float ty, float tz);
mat4 mat4_scale(float sx, float sy, float sz);
mat4 mat4_rotate_xyz(float rx, float ry, float rz);
mat4 mat4_frustum_asymetric(float left, float right, float bottom, float top, float near, float far);
mat4 mat4_mul(mat4 a, mat4 b);
vec4_t mat4_mul_vec4(mat4 m, vec4_t v);  // Add this for vec4 transformation

// ------------------ Vector Functions ------------------

void updateSph(vec3_t *v);                  // Cartesian → Spherical
void updateCar(vec3_t *v);                  // Spherical → Cartesian

// Converting degrees to
float degToRad(float ang_deg);

vec3_t vec3_from_spherical(double r, double theta, double phi);
vec3_t vec3_normalize_fast(vec3_t v);
vec3_t vec3_slerp(vec3_t a, vec3_t b, double t);
vec3_t vec3_scale(vec3_t v, float s);
vec3_t vec3_add(vec3_t u, vec3_t v);
vec3_t vec3_sub(vec3_t u, vec3_t v);
float vec3_dot(vec3_t u, vec3_t v);


#endif

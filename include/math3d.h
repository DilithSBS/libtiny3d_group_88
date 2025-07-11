/*
    All the functions related to mathematical concepts and logics are included here
*/

#ifndef MATH3D_H
#define MATH3D_H

#include <stdio.h>
#include <math.h>

// ------------------ Vector Structures ------------------//

// Store 3D vectors
typedef struct {
    double x, y, z;         // As cartesian coordinates
    double r, theta, phi;   // As spherical coordinates
} vec3_t;

// strore 4D vectors
typedef struct {
    float x, y, z, w;
} vec4_t;


// ------------------ Vector Functions ------------------//

void updateSph(vec3_t *v);      // Cartesian to Spherical coordinates
void updateCar(vec3_t *v);      // Spherical to Cartesian coordinates

// Converting degrees to radians
float degToRad(float ang_deg);

// Obtain the vector when the spherical coordinates are given
vec3_t vec3_from_spherical(double r, double theta, double phi);

// Normalising vector using fast inverse square root trick
vec3_t vec3_normalize_fast(vec3_t v);

// Function for smooth rotations and movements
vec3_t vec3_slerp(vec3_t a, vec3_t b, double t);

// Multiply a 3D vector by a scalar
vec3_t vec3_scale(vec3_t v, float s);

// Add two 3D vectors
vec3_t vec3_add(vec3_t u, vec3_t v);

// Substract two 3D vectors
vec3_t vec3_sub(vec3_t u, vec3_t v);

// Dot product of two 3D vectors
float vec3_dot(vec3_t u, vec3_t v);


// ------------------ Matrix Structure ------------------//

typedef struct {
    float element[16]; // Column-major 4x4 matrix
} mat4;

// ------------------ Matrix Functions ------------------//

// 4x4 identity matrix
mat4 mat4_identity();

// Moves the object on the 3D space
mat4 mat4_translate(float tx, float ty, float tz);

// Scaling matrice that scales the objects
mat4 mat4_scale(float sx, float sy, float sz);                  

// 3D rotation matrix around x, y and z axes
mat4 mat4_rotate_xyz(float rx, float ry, float rz);    

// A perspective projection matrix using asymetric frustum bounds.
mat4 mat4_frustum_asymetric(float left, float right, float bottom, float top, float near, float far);

// Multiply two 4x4 matrices
mat4 mat4_mul(mat4 a, mat4 b);

// Multiply 4x4 matrix by a 4D vector
vec4_t mat4_mul_vec4(mat4 m, vec4_t v);  // For vec4 transformation


//--------------------Quaternion rotation structure-----------------//
// store 4D vectors
typedef struct {
    float x, y, z, w;
} quat_t;

//--------------------Quaternion rotation functions-----------------//

// Create a quaternion from an axis-angle representation
quat_t quat_from_axis_angle(vec3_t axis, float angle_rad);

// Normalize a quaternion to ensure it represent a valid rotation withouth any rotation bug
quat_t quat_normalize(quat_t q);

// Interpolates between two quaternins using SLERP
quat_t quat_slerp(quat_t a, quat_t b, float t);

// Convert a quaternion to 4x4 matrix
mat4 quat_to_mat4(quat_t q);


#endif

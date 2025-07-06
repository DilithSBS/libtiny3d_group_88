#include <stdio.h>
#include <math.h>
#include "../include/math3d.h"

// Upadate spherical coordinates using cartesian coordinates
void updateSph(vec3_t *v) {

    v-> r = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
    v-> theta = atan2f(v->y, v->x);
    if (v->r != 0) v-> phi = acos(v->z / v->r);

}

// Update cartesian coordinates using polar coordinates
void updateCar(vec3_t *v) {

    v->x = v->r * sin(v->phi) * cos(v->theta);
    v->y = v->r * sin(v->phi) * sin(v->theta);
    v->z = v->r * cos(v->phi);

}

// Converting degrees to radians
float degToRad(float ang_deg) {
    float ang_rad = ang_deg *(3.14159265358979323846f / 180.0f);
    return ang_rad;
}

vec3_t vec3_from_spherical (double r, double theta, double phi) {

    vec3_t v;

    v.r = r;
    v.theta = theta;
    v.phi = phi;

    v.x = r * sin(phi) * cos(theta);
    v.y = r * sin(phi) * sin(theta);
    v.z = r * cos(phi);

    return v;

}

#include <stdint.h>

float invSqRoot(float number) {
    if (number <= 0.0f) return 0.0f;  // Prevent invalid input

    float x2 = number * 0.5F;
    float y = number;
    const float threehalfs = 1.5F;

    union {
        float f;
        int32_t i;
    } conv;

    conv.f = y;
    conv.i = 0x5f3759df - (conv.i >> 1);  // Magic bit hack
    y = conv.f;

    // First iteration
    y = y * (threehalfs - (x2 * y * y));

    // second iteration for better precision
    y = y * (threehalfs - (x2 * y * y));

    return y;
}


vec3_t vec3_normalize_fast(vec3_t v) {

    float lenSq = v.x * v.x + v.y * v.y + v.z * v.z;
    float invLen = invSqRoot(lenSq);

    v.x *= invLen;
    v.y *= invLen;
    v.z *= invLen;

    return v;
}

vec3_t vec3_slerp(vec3_t a, vec3_t b, double t) {

    a = vec3_normalize_fast(a);
    b = vec3_normalize_fast(b);

    // Dot product of the two vectors
    double dot_prod = a.x * b.x + a.y * b.y + a.z * b.z;

    double alpha = acos(dot_prod);       // angle between a and b
    double sinAlpha = sin(alpha);

    // If the angle is very small, fall back to lerp (to avoid division by zero)
    if (sinAlpha < 1e-6) {
        vec3_t v;
        v.x = a.x + (b.x - a.x) * t;
        v.y = a.y + (b.y - a.y) * t;
        v.z = a.z + (b.z - a.z) * t;
        return vec3_normalize_fast(v);
    }

    double w1 = sin((1.0 - t) * alpha) / sinAlpha;
    double w2 = sin(t * alpha) / sinAlpha;

    vec3_t v;
    v.x = w1 * a.x + w2 * b.x;
    v.y = w1 * a.y + w2 * b.y;
    v.z = w1 * a.z + w2 * b.z;
    return vec3_normalize_fast(v);

}

// Multiplication of 3 dimensional vector by a scalar
vec3_t vec3_scale(vec3_t v, float s) {
    return (vec3_t){ v.x * s, v.y * s, v.z * s };
}

// Add two 3 dimensional vectors
vec3_t vec3_add(vec3_t u, vec3_t v) {
    return (vec3_t){ u.x + v.x, u.y + v.y, u.z + v.z};   
}

// Substract two 3 dimensional vectors
vec3_t vec3_sub(vec3_t u, vec3_t v) {
    return (vec3_t){ u.x - v.x, u.y - v.y, u.z - v.z};   
}

// Dot product of two 3 dimensional vectors
float vec3_dot(vec3_t u, vec3_t v) {
    return (float)((u.x * v.x) + (u.y * v.y) + (u.z * v.z));   
}

// Creating an 4x4 identity matrix
mat4 mat4_identity() {
    mat4 result = {0};
    result.element[0] = result.element[5] = result.element[10] = result.element[15] = 1.0f;
    return result;
}

// Translation matrix 
mat4 mat4_translate(float tx, float ty, float tz) {
    mat4 result = mat4_identity();
    result.element[12] = tx;
    result.element[13] = ty;
    result.element[14] = tz;
    return result;
}

// Scale matrix
mat4 mat4_scale(float sx, float sy, float sz) {
    mat4 result = mat4_identity();
    result.element[0] = sx;
    result.element[5] = sy;
    result.element[10] = sz;
    return result;
}

// Rotation matrix
mat4 mat4_rotate_xyz(float rx, float ry, float rz) {
    float rx_rad = degToRad(rx);
    float ry_rad = degToRad(ry);
    float rz_rad = degToRad(rz);

    float sin_x = sinf(rx_rad), cos_x = cosf(rx_rad);
    float sin_y = sinf(ry_rad), cos_y = cosf(ry_rad);
    float sin_z = sinf(rz_rad), cos_z = cosf(rz_rad);

    // Rotation matrix around x axis
    mat4 rxm = mat4_identity();
    rxm.element[5] = cos_x;
    rxm.element[6] = sin_x;
    rxm.element[9] = -sin_x;
    rxm.element[10] = cos_x;

    // Rotation matrix
    mat4 rym = mat4_identity();
    rym.element[0] = cos_y;
    rym.element[2] = -sin_y;
    rym.element[8] = sin_y;
    rym.element[10] = cos_y;

    mat4 rzm = mat4_identity();
    rzm.element[0] = cos_z; 
    rzm.element[1] = sin_z;
    rzm.element[4] = -sin_z; 
    rzm.element[5] = cos_z;

    return mat4_mul(rzm, mat4_mul(rym, rxm));
}

mat4 mat4_frustum_asymetric(float left, float right, float bottom, float top, float near, float far) {
    mat4 result = {0};
    result.element[0] = (2.0f * near) / (right - left);
    result.element[5] = (2.0f * near) / (top - bottom);
    result.element[8] = (right + left) / (right - left);
    result.element[9] = (top + bottom) / (top - bottom);
    result.element[10] = -(far + near) / (far - near);
    result.element[11] = -1.0f;
    result.element[14] = -(2.0f * far * near) / (far - near);
    return result;
}

mat4 mat4_mul(mat4 a, mat4 b) {
    mat4 result = {0};

    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            float sum = 0.0f;
            for (int k = 0; k < 4; ++k) {
                sum += a.element[k * 4 + row] * b.element[col * 4 + k];
            }
            result.element[col * 4 + row] = sum;
        }
    }

    return result;
}

vec4_t mat4_mul_vec4(mat4 m, vec4_t v) {
    vec4_t result;

    result.x = m.element[0]*v.x + m.element[4]*v.y + m.element[8]*v.z + m.element[12]*v.w;
    result.y = m.element[1]*v.x + m.element[5]*v.y + m.element[9]*v.z + m.element[13]*v.w;
    result.z = m.element[2]*v.x + m.element[6]*v.y + m.element[10]*v.z + m.element[14]*v.w;
    result.w = m.element[3]*v.x + m.element[7]*v.y + m.element[11]*v.z + m.element[15]*v.w;

    return result;
}

quat_t quat_from_axis_angle(vec3_t axis, float angle_rad) {
    float half = angle_rad * 0.5f;
    float sin_half = sinf(half);
    return (quat_t){
        .w = cosf(half),
        .x = axis.x * sin_half,
        .y = axis.y * sin_half,
        .z = axis.z * sin_half
    };
}

quat_t quat_normalize(quat_t q) {
    float mag = sqrtf(q.w*q.w + q.x*q.x + q.y*q.y + q.z*q.z);
    return (quat_t){ q.w / mag, q.x / mag, q.y / mag, q.z / mag };
}

quat_t quat_slerp(quat_t a, quat_t b, float t) {
    float dot = a.w*b.w + a.x*b.x + a.y*b.y + a.z*b.z;

    if (dot < 0.0f) {
        b.w = -b.w; b.x = -b.x; b.y = -b.y; b.z = -b.z;
        dot = -dot;
    }

    if (dot > 0.9995f) {
        // Linear interpolation for very small angles
        quat_t result = {
            a.w + t*(b.w - a.w),
            a.x + t*(b.x - a.x),
            a.y + t*(b.y - a.y),
            a.z + t*(b.z - a.z)
        };
        return quat_normalize(result);
    }

    float theta_0 = acosf(dot);
    float theta = theta_0 * t;
    float sin_theta = sinf(theta);
    float sin_theta_0 = sinf(theta_0);

    float s0 = cosf(theta) - dot * sin_theta / sin_theta_0;
    float s1 = sin_theta / sin_theta_0;

    return (quat_t){
        a.w * s0 + b.w * s1,
        a.x * s0 + b.x * s1,
        a.y * s0 + b.y * s1,
        a.z * s0 + b.z * s1
    };
}

mat4 quat_to_mat4(quat_t q) {
    mat4 m = {0};

    float x = q.x, y = q.y, z = q.z, w = q.w;

    m.element[0] = 1 - 2*y*y - 2*z*z;
    m.element[1] = 2*x*y + 2*w*z;
    m.element[2] = 2*x*z - 2*w*y;
    m.element[3] = 0;

    m.element[4] = 2*x*y - 2*w*z;
    m.element[5] = 1 - 2*x*x - 2*z*z;
    m.element[6] = 2*y*z + 2*w*x;
    m.element[7] = 0;

    m.element[8] = 2*x*z + 2*w*y;
    m.element[9] = 2*y*z - 2*w*x;
    m.element[10] = 1 - 2*x*x - 2*y*y;
    m.element[11] = 0;

    m.element[12] = 0;
    m.element[13] = 0;
    m.element[14] = 0;
    m.element[15] = 1;

    return m;
}

#include <math.h>
#include "math3d.h"

void updateSph(vec3_t *v) {

    v-> r = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
    v-> theta = atan2f(v->y, v->x);
    if (v->r != 0) v-> phi = acos(v->z / v->r);

}

void updateCar(vec3_t *v) {

    v->x = v->r * sin(v->phi) * cos(v->theta);
    v->y = v->r * sin(v->phi) * sin(v->theta);
    v->z = v->r * cos(v->phi);

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

float invSqRoot(float number) {

    long i;         // 32-bit integer for bit-level hacking
    float x2, y;    // helping floats

    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y = number;
    i = *(long *) &y;
    i = 0x5f3759df - (i >> 1);
    y = *(float *) &i;
    y = y * (threehalfs - (x2 * y * y));

    return y;
    
}

void vec3_normalize_fast(vec3_t *v) {

    float lenSq = v->x * v->x + v->y * v->y + v->z * v->z;
    float invLen = invSqRoot(lenSq);

    v->x *= invLen;
    v->y *= invLen;
    v->z *= invLen;

}
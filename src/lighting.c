#include "../include/math3d.h"
#include "../include/lighting.h"

// Computes brightness of a line based on Lambert's cosine law
float compute_line_intensity(vec3_t p1, vec3_t p2, vec3_t light_dir) {
    vec3_t edge_dir = vec3_sub(p2, p1);
    vec3_t norm_edge = vec3_normalize_fast(edge_dir);
    vec3_t norm_light = vec3_normalize_fast(light_dir);

    float dot_product = vec3_dot(norm_edge, norm_light);
    return fmaxf(0.0f, dot_product);  // Clamp to [0, 1]
}

float compute_multi_light_intensity(vec3_t p1, vec3_t p2, vec3_t* lights, int light_count) {
    float intensity = 0.0f;
    for (int i = 0; i < light_count; i++) {
        intensity += compute_line_intensity(p1, p2, lights[i]);
    }
    return fminf(1.0f, intensity); // Clamp total intensity to 1.0
}

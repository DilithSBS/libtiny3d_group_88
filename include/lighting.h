#ifndef LIGHTNING_H
#define LIGHTNING_H


// Computes brightness of a line based on Lambert's cosine law
float compute_line_intensity(vec3_t p1, vec3_t p2, vec3_t light_dir);

float compute_multi_light_intensity(vec3_t p1, vec3_t p2, vec3_t* lights, int light_count);

#endif
=======
#ifndef LIGHTNING_H
#define LIGHTNING_H


// Computes brightness of a line based on Lambert's cosine law
float compute_line_intensity(vec3_t p1, vec3_t p2, vec3_t light_dir);

float compute_multi_light_intensity(vec3_t p1, vec3_t p2, vec3_t* lights, int light_count);

#endif


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "../include/tiny3d.h"

#define WIDTH 800
#define HEIGHT 800
#define PI 3.14159265f
#define FRAME_COUNT 200

void generate_octahedron(vec3_t** out_vertices, int* out_vcount, int (**out_edges)[2], int* out_ecount) {
    *out_vcount = 12;
    *out_ecount = 18;

    *out_vertices = malloc(sizeof(vec3_t) * (*out_vcount));
    *out_edges = malloc(sizeof(int[2]) * (*out_ecount));

    vec3_t hex_prism_vertices[12] = {
        {cos(0), sin(0), -1}, {cos(PI/3), sin(PI/3), -1},
        {cos(2*PI/3), sin(2*PI/3), -1}, {cos(PI), sin(PI), -1},
        {cos(4*PI/3), sin(4*PI/3), -1}, {cos(5*PI/3), sin(5*PI/3), -1},
        {cos(0), sin(0), 1}, {cos(PI/3), sin(PI/3), 1},
        {cos(2*PI/3), sin(2*PI/3), 1}, {cos(PI), sin(PI), 1},
        {cos(4*PI/3), sin(4*PI/3), 1}, {cos(5*PI/3), sin(5*PI/3), 1}
    };

    int hex_prism_edges[18][2] = {
        {0,1}, {1,2}, {2,3}, {3,4}, {4,5}, {5,0},
        {6,7}, {7,8}, {8,9}, {9,10}, {10,11}, {11,6},
        {0,6}, {1,7}, {2,8}, {3,9}, {4,10}, {5,11}
    };

    for (int i = 0; i < *out_vcount; i++) (*out_vertices)[i] = hex_prism_vertices[i];
    for (int i = 0; i < *out_ecount; i++) {
        (*out_edges)[i][0] = hex_prism_edges[i][0];
        (*out_edges)[i][1] = hex_prism_edges[i][1];
    }
}

vec3_t light_dirs[] = {
    {1, 1, -1}, {-1, 1, -0.5}
};

vec3_t bezier_p0 = { -2.5, 0, -5 };
vec3_t bezier_p1 = { -1, 0, -5 };
vec3_t bezier_p2 = { 1, 0, -5 };
vec3_t bezier_p3 = { 2.5, 0, -5 };

int main() {
    vec3_t* vertices = NULL;
    int vertex_count;
    int (*edges)[2] = NULL;
    int edge_count;

    generate_octahedron(&vertices, &vertex_count, &edges, &edge_count);

    for (int frame = 0; frame < FRAME_COUNT; frame++) {
        canvas_t *canvas = canvas_create(WIDTH, HEIGHT);
        if (!canvas) {
            fprintf(stderr, "Failed to create canvas.\n");
            return 1;
        }

        for (size_t y = 0; y < HEIGHT; ++y) {
            for (size_t x = 0; x < WIDTH; ++x) {
                canvas->pixels[y][x] = 0.0f;
            }
        }

        float time = (float)frame / FRAME_COUNT;
        float angle = time * 2.0f * PI;

        vec3_t anim_pos = vec3_bezier(bezier_p0, bezier_p1, bezier_p2, bezier_p3, time);

        quat_t q0 = quat_from_axis_angle((vec3_t){0, 1, 0}, 0.0f);
        quat_t q1 = quat_from_axis_angle((vec3_t){0, 1, 0}, 2.0f * PI);
        quat_t q = quat_slerp(q0, q1, time);
        mat4 rotate = quat_to_mat4(q);

        mat4 scale = mat4_scale(1.0f, 1.0f, 1.0f);
        mat4 translate = mat4_translate(anim_pos.x, anim_pos.y, anim_pos.z);
        mat4 model = mat4_mul(translate, mat4_mul(rotate, scale));

        mat4 view = mat4_identity();
        mat4 proj = mat4_frustum_asymetric(-1, 1, -1, 1, 1.0f, 10.0f);
        mat4 mvp = mat4_mul(proj, mat4_mul(view, model));

        vec3_t* projected = malloc(sizeof(vec3_t) * vertex_count);
        for (int i = 0; i < vertex_count; i++) {
            projected[i] = project_vertex(vertices[i], mvp, WIDTH, HEIGHT);
        }

        for (int i = 0; i < edge_count; i++) {
            int idx0 = edges[i][0];
            int idx1 = edges[i][1];
            vec3_t p0 = projected[idx0];
            vec3_t p1 = projected[idx1];

            if (clip_to_circular_viewport(canvas, p0.x, p0.y) &&
                clip_to_circular_viewport(canvas, p1.x, p1.y)) {

                float brightness = compute_multi_light_intensity(vertices[idx0], vertices[idx1], light_dirs, 2);
                draw_line_f(canvas, p0.x, p0.y, p1.x, p1.y, brightness);
            }
        }

        char filename[64];
        snprintf(filename, sizeof(filename), "build/frames/frame_%03d.pgm", frame);
        FILE* f = fopen(filename, "w");
        if (f) {
            fprintf(f, "P2\n%d %d\n255\n", WIDTH, HEIGHT);
            for (size_t y = 0; y < HEIGHT; y++) {
                for (size_t x = 0; x < WIDTH; x++) {
                    int value = (int)(255.0f * canvas->pixels[y][x]);
                    if (value > 255) value = 255;
                    fprintf(f, "%d ", value);
                }
                fprintf(f, "\n");
            }
            fclose(f);
            printf("Saved frame: %s\n", filename);
        }

        canvas_destroy(canvas);
        free(projected);
    }

    free(vertices);
    free(edges);

    return 0;
}

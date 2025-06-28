#include <stdio.h>
#include <math.h>
#include <time.h>

#include "../include/tiny3d.h"

#define WIDTH 200
#define HEIGHT 200
#define PI 3.14159265f
#define FRAME_COUNT 100

// Simple cube for testing wireframe
vec3_t cube_vertices[] = {
    {-1, -1, -1}, {1, -1, -1}, {1, 1, -1}, {-1, 1, -1},
    {-1, -1,  1}, {1, -1,  1}, {1, 1,  1}, {-1, 1,  1}
};

int cube_edges[][2] = {
    {0,1}, {1,2}, {2,3}, {3,0},
    {4,5}, {5,6}, {6,7}, {7,4},
    {0,4}, {1,5}, {2,6}, {3,7}
};

vec3_t light_dirs[] = {
    {1, 1, -1}, {-1, 1, -0.5}
};

vec3_t bezier_p0 = { -1.5, 0, -5 };
vec3_t bezier_p1 = { -0.5, 2, -5 };
vec3_t bezier_p2 = { 0.5, -2, -5 };
vec3_t bezier_p3 = { 1.5, 0, -5 };

int main() {
    for (int frame = 0; frame < FRAME_COUNT; frame++) {
        canvas_t *canvas = canvas_create(WIDTH, HEIGHT);
        if (!canvas) {
            fprintf(stderr, "Failed to create canvas.\n");
            return 1;
        }

        float time = (float)frame / FRAME_COUNT;
        float t = time * 10.0f;  // spin faster

        vec3_t anim_pos = vec3_bezier(bezier_p0, bezier_p1, bezier_p2, bezier_p3, time);

        mat4 rotate = mat4_rotate_xyz(t, t * 0.5f, 0);
        mat4 translate = mat4_translate(anim_pos.x, anim_pos.y, anim_pos.z);
        mat4 model = mat4_mul(translate, rotate);

        mat4 view = mat4_identity();
        mat4 proj = mat4_frustum_asymetric(-1, 1, -1, 1, 1.0f, 10.0f);
        mat4 mvp = mat4_mul(proj, mat4_mul(view, model));

        int vcount = sizeof(cube_vertices) / sizeof(vec3_t);
        int ecount = sizeof(cube_edges) / sizeof(cube_edges[0]);

        vec3_t projected[vcount];
        for (int i = 0; i < vcount; i++) {
            projected[i] = project_vertex(cube_vertices[i], mvp, WIDTH, HEIGHT);
        }

        for (int i = 0; i < ecount; i++) {
            int idx0 = cube_edges[i][0];
            int idx1 = cube_edges[i][1];
            vec3_t p0 = projected[idx0];
            vec3_t p1 = projected[idx1];

            if (clip_to_circular_viewport(canvas, p0.x, p0.y) && clip_to_circular_viewport(canvas, p1.x, p1.y)) {
                float brightness = compute_multi_light_intensity(cube_vertices[idx0], cube_vertices[idx1], light_dirs, 2);
                draw_line_f(canvas, p0.x, p0.y, p1.x, p1.y, brightness);
            }
        }

        // Save frame as PGM
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
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "../include/tiny3d.h"

#define WIDTH 400
#define HEIGHT 400
#define PI 3.14159265f
#define FRAME_COUNT 100         // Frame count to be created

// Pseudo-code
void generate_soccer_ball(vec3_t** out_vertices, int* out_vcount, int (**out_edges)[2], int* out_ecount) {
    // For simplicity, just generate a cube or icosahedron here
    // Real truncated icosahedron would need ~60 vertices and 90 edges

    *out_vcount = 60;
    *out_ecount = 90;

    // Allocate memory for vertices
    *out_vertices = malloc(sizeof(vec3_t) * (*out_vcount));

    // Allocate memory for edges
    *out_edges = malloc(sizeof(int[2]) * (*out_ecount));
   
    vec3_t soccer_ball_vertices[60] = {
        { -0.979432f, 0.000000f,  -0.201774f },
        { -0.979432f, 0.000000f,   0.201774f },
        { -0.854729f, -0.326477f, -0.403548f },
        { -0.854729f, -0.326477f,  0.403548f },
        { -0.854729f,  0.326477f, -0.403548f },
        { -0.854729f,  0.326477f,  0.403548f },
        { -0.403548f, -0.854729f, -0.326477f },
        { -0.403548f, -0.854729f,  0.326477f },
        { -0.403548f,  0.854729f, -0.326477f },
        { -0.403548f,  0.854729f,  0.326477f },
        { -0.326477f, -0.403548f, -0.854729f },
        { -0.326477f, -0.403548f,  0.854729f },
        { -0.326477f,  0.403548f, -0.854729f },
        { -0.326477f,  0.403548f,  0.854729f },
        { -0.201774f, -0.979432f,  0.000000f },
        { -0.201774f,  0.979432f,  0.000000f },
        {  0.000000f, -0.201774f, -0.979432f },
        {  0.000000f, -0.201774f,  0.979432f },
        {  0.000000f,  0.201774f, -0.979432f },
        {  0.000000f,  0.201774f,  0.979432f },
        {  0.201774f, -0.979432f,  0.000000f },
        {  0.201774f,  0.979432f,  0.000000f },
        {  0.326477f, -0.403548f, -0.854729f },
        {  0.326477f, -0.403548f,  0.854729f },
        {  0.326477f,  0.403548f, -0.854729f },
        {  0.326477f,  0.403548f,  0.854729f },
        {  0.403548f, -0.854729f, -0.326477f },
        {  0.403548f, -0.854729f,  0.326477f },
        {  0.403548f,  0.854729f, -0.326477f },
        {  0.403548f,  0.854729f,  0.326477f },
        {  0.854729f, -0.326477f, -0.403548f },
        {  0.854729f, -0.326477f,  0.403548f },
        {  0.854729f,  0.326477f, -0.403548f },
        {  0.854729f,  0.326477f,  0.403548f },
        {  0.979432f,  0.000000f, -0.201774f },
        {  0.979432f,  0.000000f,  0.201774f },
    };

    int soccer_ball_edges[90][2] = {
        { 0, 1 },   { 1, 2 },   { 2, 3 },   { 3, 4 },   { 4, 5 },
        { 5, 6 },   { 6, 7 },   { 7, 8 },   { 8, 9 },   { 9, 10 },
        { 10, 11 }, { 11, 12 }, { 12, 13 }, { 13, 14 }, { 14, 15 },
        { 15, 16 }, { 16, 17 }, { 17, 18 }, { 18, 19 }, { 19, 20 },
        { 20, 21 }, { 21, 22 }, { 22, 23 }, { 23, 24 }, { 24, 25 },
        { 25, 26 }, { 26, 27 }, { 27, 28 }, { 28, 29 }, { 29, 30 },
        { 30, 31 }, { 31, 32 }, { 32, 33 }, { 33, 34 }, { 34, 35 },
        { 35, 0 },  { 1, 36 },  { 2, 37 },  { 3, 38 },  { 4, 39 },
        { 5, 40 },  { 6, 41 },  { 7, 42 },  { 8, 43 },  { 9, 44 },
        { 10, 45 }, { 11, 46 }, { 12, 47 }, { 13, 48 }, { 14, 49 },
        { 15, 50 }, { 16, 51 }, { 17, 52 }, { 18, 53 }, { 19, 54 },
        { 20, 55 }, { 21, 56 }, { 22, 57 }, { 23, 58 }, { 24, 59 },
        { 25, 0 },  { 26, 1 },  { 27, 2 },  { 28, 3 },  { 29, 4 },
        { 30, 5 },  { 31, 6 },  { 32, 7 },  { 33, 8 },  { 34, 9 },
        { 35, 10 }, { 36, 11 }, { 37, 12 }, { 38, 13 }, { 39, 14 },
        { 40, 15 }, { 41, 16 }, { 42, 17 }, { 43, 18 }, { 44, 19 },
        { 45, 20 }, { 46, 21 }, { 47, 22 }, { 48, 23 }, { 49, 24 },
        { 50, 25 }, { 51, 26 }, { 52, 27 }, { 53, 28 }, { 54, 29 }
    };

    for (int i = 0; i < *out_vcount; i++) (*out_vertices)[i] = soccer_ball_vertices[i];
    for (int i = 0; i < *out_ecount; i++) (*out_edges)[i][0] = soccer_ball_edges[i][0], (*out_edges)[i][1] = soccer_ball_edges[i][1];

}

// Simple cube for testing wireframe
// vec3_t cube_vertices[] = {
//     {-1, -1, -1}, {1, -1, -1}, {1, 1, -1}, {-1, 1, -1},
//     {-1, -1,  1}, {1, -1,  1}, {1, 1,  1}, {-1, 1,  1}
// };

// int cube_edges[][2] = {
//     {0,1}, {1,2}, {2,3}, {3,0},
//     {4,5}, {5,6}, {6,7}, {7,4},
//     {0,4}, {1,5}, {2,6}, {3,7}
// };

vec3_t light_dirs[] = {
    {1, 1, -1}, {-1, 1, -0.5}
};

vec3_t bezier_p0 = { -1.5, 0, -5 };
vec3_t bezier_p1 = { -0.5, 2, -5 };
vec3_t bezier_p2 = { 0.5, -2, -5 };
vec3_t bezier_p3 = { 1.5, 0, -5 };

int main() {
    // Load soccer ball data
    vec3_t* vertices = NULL;
    int vertex_count;
    int (*edges)[2] = NULL;
    int edge_count;

    generate_soccer_ball(&vertices, &vertex_count, &edges, &edge_count);

    for (int frame = 0; frame < FRAME_COUNT; frame++) {

        canvas_t *canvas = canvas_create(WIDTH, HEIGHT);
        if (!canvas) {
            fprintf(stderr, "Failed to create canvas.\n");
            return 1;
        }

        // Clear the canvas before drawing the current frame
        for (size_t y = 0; y < HEIGHT; ++y) {
            for (size_t x = 0; x < WIDTH; ++x) {
                canvas->pixels[y][x] = 0.0f;
            }
        }

        // Animate t parameter and movement along Bezier curve
        float time = (float)frame / FRAME_COUNT;
        float t = time * 10.0f;

        vec3_t anim_pos = vec3_bezier(bezier_p0, bezier_p1, bezier_p2, bezier_p3, time);

        // Transformation matrices
        mat4 rotate = mat4_rotate_xyz(t, t * 0.5f, 0.0f);
        mat4 translate = mat4_translate(anim_pos.x, anim_pos.y, anim_pos.z);
        mat4 model = mat4_mul(translate, rotate);

        mat4 view = mat4_identity(); // no custom camera yet
        mat4 proj = mat4_frustum_asymetric(-1, 1, -1, 1, 1.0f, 10.0f);
        mat4 mvp = mat4_mul(proj, mat4_mul(view, model));

        // Project all soccer ball vertices
        vec3_t* projected = malloc(sizeof(vec3_t) * vertex_count);
        for (int i = 0; i < vertex_count; i++) {
            projected[i] = project_vertex(vertices[i], mvp, WIDTH, HEIGHT);
        }

        // Draw all edges with circular clipping + lighting
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

        // Export frame to PGM
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

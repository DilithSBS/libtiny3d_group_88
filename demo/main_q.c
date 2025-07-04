#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "../include/tiny3d.h"

#define WIDTH 800
#define HEIGHT 800
#define PI 3.14159265f
#define FRAME_COUNT 200         // Frame count to be created


// typedef struct {
//     int a, b;
// } edge_t;

// bool edge_equals(edge_t e1, edge_t e2) {
//     return (e1.a == e2.a && e1.b == e2.b) || (e1.a == e2.b && e1.b == e2.a);
// }

// bool edge_exists(edge_t* edges, int count, edge_t new_edge) {
//     for (int i = 0; i < count; i++) {
//         if (edge_equals(edges[i], new_edge)) return true;
//     }
//     return false;
// }

// void build_edges_from_faces(int faces[][3], int face_count, edge_t** out_edges, int* out_edge_count) {
//     int capacity = face_count * 3;
//     edge_t* edges = malloc(sizeof(edge_t) * capacity);
//     int count = 0;

//     for (int i = 0; i < face_count; i++) {
//         int* f = faces[i];
//         edge_t e1 = {f[0], f[1]};
//         edge_t e2 = {f[1], f[2]};
//         edge_t e3 = {f[2], f[0]};

//         if (!edge_exists(edges, count, e1)) edges[count++] = e1;
//         if (!edge_exists(edges, count, e2)) edges[count++] = e2;
//         if (!edge_exists(edges, count, e3)) edges[count++] = e3;
//     }

//     *out_edges = edges;
//     *out_edge_count = count;
// }

// void generate_soccer_ball(vec3_t** out_vertices, int* out_vcount, int (**out_edges)[2], int* out_ecount) {
//     double sqrt5 = sqrt(5.0);
//     float C0 = 3 * (sqrt5 - 1) / 4.0f;
//     float C1 = 9 * (9 + sqrt5) / 76.0f;
//     float C2 = 9 * (7 + 5 * sqrt5) / 76.0f;
//     float C3 = 3 * (1 + sqrt5) / 4.0f;

//     vec3_t vertices[] = {
//         { 0, C0, C3}, { 0, C0, -C3}, { 0, -C0, C3}, { 0, -C0, -C3},
//         { C3, 0, C0}, { C3, 0, -C0}, {-C3, 0, C0}, {-C3, 0, -C0},
//         { C0, C3, 0}, { C0, -C3, 0}, {-C0, C3, 0}, {-C0, -C3, 0},
//         { C1, 0, C2}, { C1, 0, -C2}, {-C1, 0, C2}, {-C1, 0, -C2},
//         { C2, C1, 0}, { C2, -C1, 0}, {-C2, C1, 0}, {-C2, -C1, 0},
//         { 0, C2, C1}, { 0, C2, -C1}, { 0, -C2, C1}, { 0, -C2, -C1},
//         { 1.5, 1.5, 1.5}, { 1.5, 1.5, -1.5}, { 1.5, -1.5, 1.5}, { 1.5, -1.5, -1.5},
//         {-1.5, 1.5, 1.5}, {-1.5, 1.5, -1.5}, {-1.5, -1.5, 1.5}, {-1.5, -1.5, -1.5}
//     };

//     static int faces[60][3] = {
//         {12,0,2}, {12,2,26}, {12,26,4}, {12,4,24}, {12,24,0},
//         {13,3,1}, {13,1,25}, {13,25,5}, {13,5,27}, {13,27,3},
//         {14,2,0}, {14,0,28}, {14,28,6}, {14,6,30}, {14,30,2},
//         {15,1,3}, {15,3,31}, {15,31,7}, {15,7,29}, {15,29,1},
//         {16,4,5}, {16,5,25}, {16,25,8}, {16,8,24}, {16,24,4},
//         {17,5,4}, {17,4,26}, {17,26,9}, {17,9,27}, {17,27,5},
//         {18,7,6}, {18,6,28}, {18,28,10}, {18,10,29}, {18,29,7},
//         {19,6,7}, {19,7,31}, {19,31,11}, {19,11,30}, {19,30,6},
//         {20,8,10}, {20,10,28}, {20,28,0}, {20,0,24}, {20,24,8},
//         {21,10,8}, {21,8,25}, {21,25,1}, {21,1,29}, {21,29,10},
//         {22,11,9}, {22,9,26}, {22,26,2}, {22,2,30}, {22,30,11},
//         {23,9,11}, {23,11,31}, {23,31,3}, {23,3,27}, {23,27,9}
//     };

//     edge_t* edges;
//     int edge_count;
//     build_edges_from_faces(faces, 60, &edges, &edge_count);

//     int (*edge_array)[2] = malloc(sizeof(int[2]) * edge_count);
//     for (int i = 0; i < edge_count; i++) {
//         edge_array[i][0] = edges[i].a;
//         edge_array[i][1] = edges[i].b;
//     }

//     *out_vertices = vertices;
//     *out_vcount = sizeof(vertices) / sizeof(vec3_t);
//     *out_edges = edge_array;
//     *out_ecount = edge_count;

//     free(edges);
// }

void generate_octahedron(vec3_t** out_vertices, int* out_vcount, int (**out_edges)[2], int* out_ecount) {
    *out_vcount = 6;
    *out_ecount = 12;

    *out_vertices = malloc(sizeof(vec3_t) * (*out_vcount));
    *out_edges = malloc(sizeof(int[2]) * (*out_ecount));

    // vec3_t octahedron_vertices[6] = {
    //     {  1,  0,  0 },
    //     { -1,  0,  0 },
    //     {  0,  1,  0 },
    //     {  0, -1,  0 },
    //     {  0,  0,  1 },
    //     {  0,  0, -1 }
    // };

    // int octahedron_edges[12][2] = {
    //     {0, 2}, {0, 3}, {0, 4}, {0, 5},
    //     {1, 2}, {1, 3}, {1, 4}, {1, 5},
    //     {2, 4}, {2, 5}, {3, 4}, {3, 5}
    // };
    // vec3_t vesak_vertices[12] = {
    //     {  0,  0,  0 },
    //     { 0.7071,  -0.7071,  0},
    //     { 0.7071,  0.7071,  0},
    //     {  1.4142,  0,  0 },

    //     {  0,  0,  1.4142},
    //     { 0.7071,  -0.7071,  1.4142},
    //     { 0.7071,  0.7071,  1.4142},
    //     {  1.4142,  0,  1.4142},

    //     {  0, -0.7071,  0.7071},
    //     {  1.4142, -0.7071,  0.7071},
    //     {  1.4142, 0.7071,  0.7071},
    //     {  0, 0.7071,  0.7071},
    // };

    // int vesak_edges[24][2] = {
    //     {0, 1}, {0, 2}, {0, 8}, {0, 11},
    //     {1, 3}, {1, 8}, {1, 9},
    //     {2, 3}, {2, 10}, {2, 11},
    //     {3, 9}, {3, 10},

    //     {4, 8}, {4, 11}, {4, 5}, {4, 6},
    //     {5, 7}, {5, 8}, {5, 9},
    //     {6, 7}, {6, 10}, {6, 11},
    //     {7, 9}, {7, 10},
    // };

    vec3_t hex_prism_vertices[12] = {
        {cos(0), sin(0), -1}, {cos(PI/3), sin(PI/3), -1},
        {cos(2*PI/3), sin(2*PI/3), -1}, {cos(PI), sin(PI), -1},
        {cos(4*PI/3), sin(4*PI/3), -1}, {cos(5*PI/3), sin(5*PI/3), -1},
        {cos(0), sin(0), 1}, {cos(PI/3), sin(PI/3), 1},
        {cos(2*PI/3), sin(2*PI/3), 1}, {cos(PI), sin(PI), 1},
        {cos(4*PI/3), sin(4*PI/3), 1}, {cos(5*PI/3), sin(5*PI/3), 1}
    };

    int hex_prism_edges[18][2] = {
        {0,1}, {1,2}, {2,3}, {3,4}, {4,5}, {5,0},       // bottom face
        {6,7}, {7,8}, {8,9}, {9,10}, {10,11}, {11,6},   // top face
        {0,6}, {1,7}, {2,8}, {3,9}, {4,10}, {5,11}      // vertical edges
    };

    // vec3_t icosahedron_vertices[12] = {
    //     { 0, 1, 1.618f }, { 0, 1, -1.618f }, { 0, -1, 1.618f }, { 0, -1, -1.618f },
    //     { 1, 1.618f, 0 }, { 1, -1.618f, 0 }, { -1, 1.618f, 0 }, { -1, -1.618f, 0 },
    //     { 1.618f, 0, 1 }, { 1.618f, 0, -1 }, { -1.618f, 0, 1 }, { -1.618f, 0, -1 }
    // };

    // int icosahedron_edges[30][2] = {
    //     {0, 2}, {0, 4}, {0, 6}, {0, 8}, {0,10},
    //     {1, 3}, {1, 4}, {1, 6}, {1, 9}, {1,11},
    //     {2, 5}, {2, 8}, {2,10},
    //     {3, 5}, {3, 9}, {3,11},
    //     {4, 8}, {4, 9},
    //     {5, 8}, {5, 9},
    //     {6,10}, {6,11},
    //     {7, 5}, {7, 9}, {7,11},
    //     {8, 9},
    //     {10,11},
    //     {2, 7}, {3, 7}, {5, 7}
    // };

    // Output the vertices
    for (int i = 0; i < *out_vcount; i++) (*out_vertices)[i] = hex_prism_vertices[i];

    // Output the edges
    for (int i = 0; i < *out_ecount; i++) {
        (*out_edges)[i][0] = hex_prism_edges[i][0]; // Starting point of the edge
        (*out_edges)[i][1] = hex_prism_edges[i][1]; // End point of the edge
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
    
    // generate_soccer_ball(&vertices, &vertex_count, &edges, &edge_count);

    // for (int frame = 0; frame < FRAME_COUNT; frame++) {

    //     canvas_t *canvas = canvas_create(WIDTH, HEIGHT);
    //     if (!canvas) {
    //         fprintf(stderr, "Failed to create canvas.\n");
    //         return 1;
    //     }

    //     for (size_t y = 0; y < HEIGHT; ++y) {
    //         for (size_t x = 0; x < WIDTH; ++x) {
    //             canvas->pixels[y][x] = 0.0f;
    //         }
    //     }

    //     float time = (float)frame / FRAME_COUNT;
    //     //float angle = time * 2.0f * PI;

    //     vec3_t anim_pos = vec3_bezier(bezier_p0, bezier_p1, bezier_p2, bezier_p3, time);

    //     quat_t q0 = quat_from_axis_angle((vec3_t){0, 1, 0}, 0.0f);
    //     quat_t q1 = quat_from_axis_angle((vec3_t){0, 1, 0}, 2.0f * PI);
    //     quat_t q = quat_slerp(q0, q1, time);
    //     mat4 rotate = quat_to_mat4(q);

    //     mat4 scale = mat4_scale(1.0f, 1.0f, 1.0f);
        
    //     //mat4 translate = mat4_translate(anim_pos.x, anim_pos.y, anim_pos.z);
    //     mat4 translate = mat4_translate(0, 0, -5);
        
    //     mat4 model = mat4_mul(translate, mat4_mul(rotate, scale));
    //     //mat4 model = mat4_mul(rotate, scale);

    //     mat4 view = mat4_identity();
    //     mat4 proj = mat4_frustum_asymetric(-1, 1, -1, 1, 1.0f, 10.0f);
    //     mat4 mvp = mat4_mul(proj, mat4_mul(view, model));

    //     vec3_t* projected = malloc(sizeof(vec3_t) * vertex_count);
    //     for (int i = 0; i < vertex_count; i++) {
    //         projected[i] = project_vertex(vertices[i], mvp, WIDTH, HEIGHT);
    //     }

    //     for (int i = 0; i < edge_count; i++) {
    //         int idx0 = edges[i][0];
    //         int idx1 = edges[i][1];
    //         vec3_t p0 = projected[idx0];
    //         vec3_t p1 = projected[idx1];

    //         if (clip_to_circular_viewport(canvas, p0.x, p0.y) &&
    //             clip_to_circular_viewport(canvas, p1.x, p1.y)) {

    //             float brightness = compute_multi_light_intensity(vertices[idx0], vertices[idx1], light_dirs, 2);
    //             draw_line_f(canvas, p0.x, p0.y, p1.x, p1.y, brightness);
    //         }
    //     }

    //     char filename[64];
    //     snprintf(filename, sizeof(filename), "build/frames/frame_%03d.pgm", frame);
    //     FILE* f = fopen(filename, "w");
    //     if (f) {
    //         fprintf(f, "P2\n%d %d\n255\n", WIDTH, HEIGHT);
    //         for (size_t y = 0; y < HEIGHT; y++) {
    //             for (size_t x = 0; x < WIDTH; x++) {
    //                 int value = (int)(255.0f * canvas->pixels[y][x]);
    //                 if (value > 255) value = 255;
    //                 fprintf(f, "%d ", value);
    //             }
    //             fprintf(f, "\n");
    //         }
    //         fclose(f);
    //         printf("Saved frame: %s\n", filename);
    //     }

    //     canvas_destroy(canvas);
    //     free(projected);
    // }

    //Generate Octahedron


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

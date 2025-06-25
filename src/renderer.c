#include <stdbool.h>
#include <stdlib.h>
#include "../include/math3d.h"
#include "../include/canvas.h"

vec3_t project_vertex(vec3_t v, mat4 mvp, int screen_width, int screen_height) {
    vec4_t v4 = {v.x, v.y, v.z, 1.0f};
    vec4_t projected = mat4_mul_vec4(mvp, v4);

    // Perspective division
    if (projected.w != 0.0f) {
        projected.x /= projected.w;
        projected.y /= projected.w;
        projected.z /= projected.w;
    }

    // Convert to screen space (NDC [-1,1] to [0, width/height])
    vec3_t screen_pos;
    screen_pos.x = (projected.x * 0.5f + 0.5f) * screen_width;
    screen_pos.y = (1.0f - (projected.y * 0.5f + 0.5f)) * screen_height;
    screen_pos.z = projected.z;

    return screen_pos;
}

bool clip_to_circular_viewport(canvas_t* canvas, float x, float y) {
    float cx = canvas->width / 2.0f;
    float cy = canvas->height / 2.0f;
    float dx = x - cx;
    float dy = y - cy;
    float radius = fmin(cx, cy);

    return (dx*dx + dy*dy) <= (radius * radius);
}

void render_wireframe(canvas_t* canvas, vec3_t* vertices, int vertex_count, int (*edges)[2], int edge_count, mat4 mvp) {
    vec3_t* projected = malloc(sizeof(vec3_t) * vertex_count);

    for (int i = 0; i < vertex_count; i++) {
        projected[i] = project_vertex(vertices[i], mvp, canvas->width, canvas->height);
    }

    for (int i = 0; i < edge_count; i++) {
        vec3_t p0 = projected[edges[i][0]];
        vec3_t p1 = projected[edges[i][1]];

        // Optional: clip or depth sort here
        if (clip_to_circular_viewport(canvas, p0.x, p0.y) &&
            clip_to_circular_viewport(canvas, p1.x, p1.y)) {

            draw_line_f(canvas, p0.x, p0.y, p1.x, p1.y, 1.0f); // thickness = 1.0
        }
    }

    free(projected);
}

// Pseudo-code
void generate_soccer_ball(vec3_t** out_vertices, int* out_vcount, int (**out_edges)[2], int* out_ecount) {
    // For simplicity, just generate a cube or icosahedron here
    // Real truncated icosahedron would need ~60 vertices and 90 edges

    static vec3_t verts[] = {
        {1,1,1},  {-1,1,1}, {-1,-1,1}, {1,-1,1},
        {1,1,-1}, {-1,1,-1}, {-1,-1,-1}, {1,-1,-1}
    };

    static int edges[][2] = {
        {0,1},{1,2},{2,3},{3,0},
        {4,5},{5,6},{6,7},{7,4},
        {0,4},{1,5},{2,6},{3,7}
    };

    *out_vertices = verts;
    *out_vcount = 8;
    *out_edges = edges;
    *out_ecount = 12;
}

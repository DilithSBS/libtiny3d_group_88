/*
    All the functions related to rendering 3D objects on the canvas are implemented here
    project_vertex()
    clip_to_circular_viewport()
    render_wireframe()
*/

#include <stdbool.h>
#include <stdlib.h>
#include "../include/math3d.h"
#include "../include/canvas.h"

// project 3D vertices into 2D canvas plane
vec3_t project_vertex(vec3_t vertex, mat4 mvp, int screen_width, int screen_height) {
    
    // Convert vec3 to vec4
    vec4_t v4 = {vertex.x, vertex.y, vertex.z, 1.0f};
    
    // Apply mvp(Model View Projection) by multiplying v4 by mvp
    vec4_t projected = mat4_mul_vec4(mvp, v4);

    // Perspective division
    if (projected.w == 0.0f) projected.w = 1e-6f; // Division by zero avoided
    projected.x /= projected.w;
    projected.y /= projected.w;
    projected.z /= projected.w;
    
    // Convert to screen space (NDC [-1,1] to [0, width/height])
    vec3_t screen_pos;
    screen_pos.x = (projected.x * 0.5f + 0.5f) * screen_width;
    screen_pos.y = (1.0f - (projected.y * 0.5f + 0.5f)) * screen_height;
    screen_pos.z = projected.z;

    // Return the 3D coordinates of the vertex
    return screen_pos;
}

// clipping edges into a circle to check if a pixel is inside a circular drawing area.
bool clip_to_circular_viewport(canvas_t* canvas, float x, float y) {
    
    // Center of the canvas
    float cx = canvas->width / 2.0f; 
    float cy = canvas->height / 2.0f;

    // distances to the from a point
    float dx = x - cx;
    float dy = y - cy;
    float radius = fmin(cx, cy);

    // return if the point is out of the boundsof the circle
    return (dx*dx + dy*dy) <= (radius * radius);
}

// draw a 3D object as a wireframe
void render_wireframe(canvas_t* canvas, vec3_t* vertices, int vertex_count, int (*edges)[2], int edge_count, mat4 mvp) {
    
    // Project all 3D vertices to 2D screen space
    vec3_t* projected = malloc(sizeof(vec3_t) * vertex_count);
    for (int i = 0; i < vertex_count; i++) {
        projected[i] = project_vertex(vertices[i], mvp, canvas->width, canvas->height);
    }

    // Draw edges between projected vertex pairs
    for (int i = 0; i < edge_count; i++) {

        int idx0 = edges[i][0];
        int idx1 = edges[i][1];        

        if (idx0 >= vertex_count || idx1 >= vertex_count) continue;
        
        vec3_t p0 = projected[idx0];
        vec3_t p1 = projected[idx1];

        // Optional: clip or depth sort here
        if (clip_to_circular_viewport(canvas, p0.x, p0.y) &&
            clip_to_circular_viewport(canvas, p1.x, p1.y)) {

            // Draw the edges
            draw_line_f(canvas, p0.x, p0.y, p1.x, p1.y, 1.0f); // thickness is set to 1.0
        }
    }
    
    free(projected);
}



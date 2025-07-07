/*
    All the functions related to rendering 3D objects on the canvas are included here
    project_vertex()
    clip_to_circular_viewport()
    render_wireframe()
*/

#ifndef RENDERER_H
#define RENDERER_H

#include <stdbool.h>

// project 3D vertices into 2D canvas plane
vec3_t project_vertex(vec3_t v, mat4 mvp, int screen_width, int screen_height);

// clipping edges into a circle to check if a pixel is inside a circular drawing area.
bool clip_to_circular_viewport(canvas_t* canvas, float x, float y);

// draw a 3D object as a wireframe
void render_wireframe(canvas_t* canvas, vec3_t* vertices, int vertex_count, int (*edges)[2], int edge_count, mat4 mvp);

#endif
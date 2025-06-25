#ifndef RENDERER_H
#define RENDERER_H

#include <stdbool.h>

vec3_t project_vertex(vec3_t v, mat4 mvp, int screen_width, int screen_height);

bool clip_to_circular_viewport(canvas_t* canvas, float x, float y);

void render_wireframe(canvas_t* canvas, vec3_t* vertices, int vertex_count, int (*edges)[2], int edge_count, mat4 mvp);
// Pseudo-code
void generate_soccer_ball(vec3_t** out_vertices, int* out_vcount, int (**out_edges)[2], int* out_ecount);


#endif

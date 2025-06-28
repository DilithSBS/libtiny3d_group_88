#include <stdio.h>
#include <math.h>
#include "../include/math3d.h"
#include "../include/canvas.h"

// Cube vertex and edge data
vec3_t cube_vertices[8] = {
    {-1, -1, -1}, {1, -1, -1},
    {1, 1, -1},  {-1, 1, -1},
    {-1, -1, 1},  {1, -1, 1},
    {1, 1, 1},   {-1, 1, 1}
};

int cube_edges[12][2] = {
    {0, 1}, {1, 2}, {2, 3}, {3, 0},
    {4, 5}, {5, 6}, {6, 7}, {7, 4},
    {0, 4}, {1, 5}, {2, 6}, {3, 7}
};

// Perspective projection and screen centering
void project_to_canvas(vec4_t v, float* x_out, float* y_out, float screen_width, float screen_height, float scale) {
    *x_out = (v.x / -v.z) * scale + screen_width / 2.0f;
    *y_out = (v.y / -v.z) * scale + screen_height / 2.0f;
}

int main() {
    const size_t width = 800, height = 800;
    canvas_t* canvas = canvas_create(width, height);

    mat4 model = mat4_translate(0, 0, -5);
    mat4 rotation = mat4_rotate_xyz(30, 45, 20);
    mat4 transform = mat4_mul(model, rotation);

    float x0, y0, x1, y1;

    for (int i = 0; i < 12; i++) {
        vec3_t a = cube_vertices[cube_edges[i][0]];
        vec3_t b = cube_vertices[cube_edges[i][1]];

        vec4_t va = {a.x, a.y, a.z, 1.0f};
        vec4_t vb = {b.x, b.y, b.z, 1.0f};

        vec4_t ta = mat4_mul_vec4(transform, va);
        vec4_t tb = mat4_mul_vec4(transform, vb);

        project_to_canvas(ta, &x0, &y0, width, height, 100.0f);
        project_to_canvas(tb, &x1, &y1, width, height, 100.0f);

        draw_line_f(canvas, x0, y0, x1, y1, 1.5f);
    }

    // Export as PGM image
    FILE* f = fopen("cube.pgm", "w");
    fprintf(f, "P2\n%zu %zu\n255\n", width, height);
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            float brightness = canvas->pixels[y][x];
            int value = (int)(brightness * 255.0f);
            if (value > 255) value = 255;
            fprintf(f, "%d ", value);
        }
        fprintf(f, "\n");
    }
    fclose(f);

    canvas_destroy(canvas);
    printf("Cube rendered to cube.pgm\n");

    return 0;
}

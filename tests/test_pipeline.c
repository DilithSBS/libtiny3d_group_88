#include <stdio.h>
#include <math.h>
#include "../include/math3d.h"
#include "../include/canvas.h"

#define WIDTH 400
#define HEIGHT 400
#define ZOOM_SCALE 400.0f
#define FRAME_COUNT 150  // Number of frames to complete the rotation

#define PI 3.14159265f

// Cube vertex and edge data
vec3_t cube_vertices[8] = {
    {-1, -1, -1}, {1, -1, -1},
    {1, 1, -1},  {-1, 1, -1},
    {-1, -1, 1},  {1, -1, 1},
    {1, 1, 1},   {-1, 1, 1}
};

int cube_edges[12][2] = {
    {0, 1}, {1, 2}, {2, 3}, {3, 0},     // Back surface
    {4, 5}, {5, 6}, {6, 7}, {7, 4},     // Front surface
    {0, 4}, {1, 5}, {2, 6}, {3, 7}      // Connecting edges
};

// Perspective projection and screen centering
void project_to_canvas(vec4_t v, float* x_out, float* y_out, float screen_width, float screen_height, float scale) {
    *x_out = (v.x / -v.z) * scale + screen_width / 2.0f;
    *y_out = (v.y / -v.z) * scale + screen_height / 2.0f;
}

int main() {
    // Create canvas
    canvas_t* canvas = canvas_create(WIDTH, HEIGHT);
    if (!canvas) {
        fprintf(stderr, "Failed to create canvas.\n");
        return 1;
    }

    // Rotation factor for smooth rotation
    float rotation_speed = 10.0f;

    for (int frame = 0; frame < FRAME_COUNT; frame++) {
        // Clear the canvas before drawing
        for (size_t y = 0; y < HEIGHT; ++y) {
            for (size_t x = 0; x < WIDTH; ++x) {
                canvas->pixels[y][x] = 0.0f;
            }
        }

        // Calculate smooth rotation angle
        float angle = (frame * rotation_speed) * 2.0f * PI / FRAME_COUNT;

        // Define transformation matrices (scale, rotation, and translation)
        mat4 scale = mat4_scale(1.0f, 1.0f, 1.0f);
        mat4 model = mat4_translate(0, 0, -5);
        mat4 rotation = mat4_rotate_xyz(angle, angle * 0.7f, angle * 0.3f);  // Continuous rotation on different axes
        mat4 transform = mat4_mul(model, mat4_mul(rotation, scale));

        // 2D coordinate projections
        float x0, y0, x1, y1;

        // Loop through edges of the cube and project to 2D
        for (int i = 0; i < 12; i++) {
            vec3_t a = cube_vertices[cube_edges[i][0]];
            vec3_t b = cube_vertices[cube_edges[i][1]];

            vec4_t va = {a.x, a.y, a.z, 1.0f};
            vec4_t vb = {b.x, b.y, b.z, 1.0f};

            vec4_t ta = mat4_mul_vec4(transform, va);
            vec4_t tb = mat4_mul_vec4(transform, vb);

            project_to_canvas(ta, &x0, &y0, WIDTH, HEIGHT, ZOOM_SCALE);
            project_to_canvas(tb, &x1, &y1, WIDTH, HEIGHT, ZOOM_SCALE);

            draw_line_f(canvas, x0, y0, x1, y1, 1.5f);
        }

        // Export as PGM image
        char filename[64];
        snprintf(filename, sizeof(filename), "frame_%03d.pgm", frame);
        canvas_save_pgm(canvas, filename);
    }

    canvas_destroy(canvas);
    printf("All frames saved to current directory.\n");

    return 0;
}

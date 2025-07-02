/*

# Task 2.2 Demo: Render a cube using 3D transforms and project to 2D canvas.

# Output: grayscale image in build/cube.pgm

*/

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
    {0, 1}, {1, 2}, {2, 3}, {3, 0},     // Back surface of the cube
    {4, 5}, {5, 6}, {6, 7}, {7, 4},     // Front surface of the cube
    {0, 4}, {1, 5}, {2, 6}, {3, 7}      // Connecting edges
};

// Projects a 3D homogeneous point (vec4_t) into 2D canvas space
void project_to_canvas(vec4_t v, float* x_out, float* y_out, float screen_width, float screen_height, float scale) {
    
     // Simple perspective projection (assumes right-handed system)
    *x_out = (v.x / -v.z) * scale + screen_width / 2.0f;
    *y_out = (v.y / -v.z) * scale + screen_height / 2.0f;
}

int main() {

    // Canvas properties initialization
    const size_t width = 1600, height = 1600;
    
    // Making the canvas
    canvas_t* canvas = canvas_create(width, height);

    // Render cube at different angles in 5 degree steps
    for (float angle = 0; angle < 360; angle += 5.0f) {
        
        // Clear the canvas before drawing the current frame
        for (size_t y = 0; y < height; ++y) {
            for (size_t x = 0; x < width; ++x) {
                canvas->pixels[y][x] = 0.0f;
            }
        }
        
        // Scaling the cube
        mat4 scale = mat4_scale(1.0f, 1.0f, 1.0f);      // 1x larger cube

        // Model matrix: move the cube -5 units into the screen
        mat4 model = mat4_translate(0, 0, -2);
        
        // Rotate cube in all 3 axes using varying angles
        mat4 rotation = mat4_rotate_xyz(angle, angle * 0.7f, angle * 0.3f);
        
        // Combine model and rotation transformations
        mat4 transform = mat4_mul(model, mat4_mul(rotation, scale));
        
        // 2D coordinate projections
        float x0, y0, x1, y1;   

        // Loop through 12 edges of the cube
        for (int i = 0; i < 12; i++) {

            // Get 3D coordinates of the edge endpoints
            vec3_t a = cube_vertices[cube_edges[i][0]];
            vec3_t b = cube_vertices[cube_edges[i][1]];

            // Convert to homogeneous coordinates (vec4_t)
            vec4_t va = {a.x, a.y, a.z, 1.0f};
            vec4_t vb = {b.x, b.y, b.z, 1.0f};

            // Apply transformation to the endpoints
            vec4_t transformed_a = mat4_mul_vec4(transform, va);
            vec4_t transformed_b = mat4_mul_vec4(transform, vb);

            // Project to 2D plane (screen)
            project_to_canvas(transformed_a, &x0, &y0, width, height, 100.0f);
            project_to_canvas(transformed_b, &x1, &y1, width, height, 100.0f);

            // Draw the projected edge as a line on the canvas
            draw_line_f(canvas, x0, y0, x1, y1, 1.5f);
        }

        // Export as PGM image
        char filename[64];
        sprintf(filename, "build/cube_frames/frame_%.0f.pgm", angle);
        canvas_save_pgm(canvas, filename);

        printf("Rendering angle %.0f\n", angle);

        
    }
    canvas_destroy(canvas);

    printf("Cube rotation frames are rendered to build/cube_frames/\n");

    return 0;
}

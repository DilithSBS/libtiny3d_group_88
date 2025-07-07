/*
    - This program was implemented to test if the math3D library is working properly
    - A 3D cube is generated on the canvas and we can manualy change the rotation angles of it by changing "X_ROT", "Y_ROT" and "Z_ROT" in degrees.
    - The output is generated as /tests/visual_tests/test_math/frame_*_*_*.pgm
    - It can be converted into .png by running the make command "make convert-test-math-png" on the terminal or run the python program with rotation angles "python test_math_png.py X_ROT Y_ROT Z_ROT".
*/

#include <stdio.h>
#include <math.h>
#include "../include/math3d.h"
#include "../include/canvas.h"

// Canvas size
#define WIDTH 1600
#define HEIGHT 1600

#define X_ROT 60.0
#define Y_ROT 30.0
#define Z_ROT 20.0

#define ZOOM_SCALE 1000.0


// Rotation angle
double angle = 30;

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

void mat4_print(mat4 m) {
    //printf("Matrix 4x4:\n");
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            printf("%8.3f ", m.element[col * 4 + row]); // column-major access
        }
        printf("\n");
    }
}


int main() {

    // Canvas properties initialization
    const size_t width = WIDTH, height = HEIGHT;
    
    // Making the canvas
    canvas_t* canvas = canvas_create(width, height);

        
    // Clear the canvas before drawing the current frame
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            canvas->pixels[y][x] = 0.0f;
        }
    }
    
    // Scaling the cube
    mat4 scale = mat4_scale(1.0f, 1.0f, 1.0f);      // 1x larger cube
    printf("Scaling: \n");
    mat4_print(scale);

    // Model matrix: move the cube -5 units into the screen
    mat4 model = mat4_translate(0, 0, -7);
    printf("Translation: \n");
    mat4_print(model);
    
    // Rotate cube in all 3 axes using varying angles
    mat4 rotation = mat4_rotate_xyz(X_ROT, Y_ROT, Z_ROT);
    printf("Rotation: \n");
    mat4_print(rotation);
    
    // Combine model and rotation transformations
    mat4 transform = mat4_mul(model, mat4_mul(rotation, scale));
    printf("Complete transformation: \n");
    mat4_print(transform);
    
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
        project_to_canvas(transformed_a, &x0, &y0, width, height, ZOOM_SCALE);
        project_to_canvas(transformed_b, &x1, &y1, width, height, ZOOM_SCALE);

        // Draw the projected edge as a line on the canvas
        draw_line_f(canvas, x0, y0, x1, y1, 4.5f);
    }

    // Export as PGM image
    char filename[64];
    sprintf(filename, "tests/visual_tests/test_math/frame_%.0f_%.0f_%.0f.pgm", X_ROT, Y_ROT, Z_ROT);
    canvas_save_pgm(canvas, filename);

    printf("Rendering angles: X_ROT = %.0f Y_ROT = %.0f Z_ROT = %.0f\n", X_ROT, Y_ROT, Z_ROT);
    

    canvas_destroy(canvas);

    return 0;
}

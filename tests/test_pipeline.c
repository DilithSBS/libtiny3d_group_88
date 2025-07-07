/*
    - This program was implemented to test if the rendering is working properly
    - A 3D soccer ball is generated on the canvas loaded from an object file
    - And it is rotated around x, y and z axes
    - The output frames are generated as /tests/visual_tests/test_pipeline/test_pipeline_*.pgm
    - These frams can be converted into .gif and .mp4 by running the make command "make convert-test-pipeline" on the terminal or run the python program "test_pipeline_gif_mp4.py".
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "../include/math3d.h"
#include "../include/canvas.h"

#define WIDTH 400           // Canvas width
#define HEIGHT 400          // Canvas height

#define ZOOM_SCALE 200.0f   // Size scale of the cube
#define FRAME_COUNT 200     // Number of frames to complete the rotation

#define MAX_VERTICES 2048
#define MAX_FACES 4096

#define PI 3.14159265f      // Initializing Pi

// Load OBJ and extract edges from triangle faces
bool load_obj(const char* filename, vec3_t** soc_vertices, int* soc_vcount, int (**soc_edges)[2], int* soc_ecount) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Could not open %s\n", filename);
        return false;
    }

    vec3_t temp_vertices[MAX_VERTICES];
    int edges_tmp[MAX_FACES * 6][2]; // supports more than triangles
    int vcount = 0, edge_count = 0;

    char line[512];
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == 'v' && line[1] == ' ') {
            vec3_t v;
            sscanf(line, "v %lf %lf %lf", &v.x, &v.y, &v.z);
            if (vcount < MAX_VERTICES) {
                temp_vertices[vcount++] = v;
            }
        } else if (line[0] == 'f') {
            int face_indices[8]; // supports up to 8-gons
            int count = 0;
            char* token = strtok(line + 2, " ");
            while (token && count < 8) {
                sscanf(token, "%d", &face_indices[count++]);
                token = strtok(NULL, " ");
            }

            for (int i = 0; i < count; i++) {
                int a = face_indices[i] - 1;
                int b = face_indices[(i + 1) % count] - 1;
                // check for duplicate edge
                int duplicate = 0;
                for (int j = 0; j < edge_count; j++) {
                    if ((edges_tmp[j][0] == a && edges_tmp[j][1] == b) || 
                        (edges_tmp[j][1] == a && edges_tmp[j][0] == b)) {
                        duplicate = 1;
                        break;
                    }
                }
                if (!duplicate && edge_count < MAX_FACES * 6) {
                    edges_tmp[edge_count][0] = a;
                    edges_tmp[edge_count][1] = b;
                    edge_count++;
                }
            }
        }
    }
    fclose(file);

    *soc_vertices = malloc(sizeof(vec3_t) * vcount);
    for (int i = 0; i < vcount; i++) (*soc_vertices)[i] = temp_vertices[i];
    *soc_vcount = vcount;

    *soc_edges = malloc(sizeof(int[2]) * edge_count);
    for (int i = 0; i < edge_count; i++) {
        (*soc_edges)[i][0] = edges_tmp[i][0];
        (*soc_edges)[i][1] = edges_tmp[i][1];
    }
    *soc_ecount = edge_count;
    return true;
}


// Perspective projection and screen centering
void project_to_canvas(vec4_t v, float* x_out, float* y_out, float screen_width, float screen_height, float scale) {
    *x_out = (v.x / -v.z) * scale + screen_width / 2.0f;
    *y_out = (v.y / -v.z) * scale + screen_height / 2.0f;
}

int main() {

    // For the soccer ball
    vec3_t* soccer_vertices = NULL;
    int soccer_vertex_count;
    int (*soccer_edges)[2] = NULL;
    int soccer_edge_count;

    // Load the soccer ball from object file
    if (!load_obj("soccer.obj", &soccer_vertices, &soccer_vertex_count, &soccer_edges, &soccer_edge_count)) return 1;

    // Create canvas
    canvas_t* canvas = canvas_create(WIDTH, HEIGHT);
    if (!canvas) {
        fprintf(stderr, "Failed to create canvas.\n");
        return 1;
    }

    // Rotation factor for smooth rotation
    float rotation_speed = 80.0f;

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
        mat4 model = mat4_translate(0, 0, -6);
        mat4 rotation = mat4_rotate_xyz(angle, angle * 0.2f, angle * 0.9f);  // Continuous rotation on different axes
        mat4 transform = mat4_mul(model, mat4_mul(rotation, scale));

        // 2D coordinate projections
        float x0, y0, x1, y1;

        // Loop through edges of the soccer ball and project to 2D
        for (int i = 0; i < 90; i++) {
            vec3_t a = soccer_vertices[soccer_edges[i][0]];
            vec3_t b = soccer_vertices[soccer_edges[i][1]];

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
        snprintf(filename, sizeof(filename), "tests/visual_tests/test_pipeline/test_pipeline_%03d.pgm", frame);
        canvas_save_pgm(canvas, filename);
    }

    canvas_destroy(canvas);
    printf("All frames saved to tests/visual_tests/test_pipeline/.\n");

    return 0;
}

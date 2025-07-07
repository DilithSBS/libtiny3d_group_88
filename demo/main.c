/*
    - This is the demonstration program of tiny3d 3D rendering library
    - It generates a soccer ball(from an object file) and a octahedron(by manual coordinates) and make them move and rotate on the canvas
    - The output frames are generated as /build/frames/frame_*.pgm
    - These frams can be converted into .gif and .mp4 by running the make command "make convert-demo" on the terminal or run the python program "demo_gif_mp4.py".
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "../include/tiny3d.h"


// Defining important parameters
#define WIDTH 400
#define HEIGHT 400
#define PI 3.14159265f
#define FRAME_COUNT 200
#define ZOOM_SCALE 100.0f
#define ROTATION_MULTIPLIER 20.0

#define MAX_VERTICES 2048
#define MAX_FACES 4096

// Initialising lighting directions
vec3_t light_dirs[] = {
    {1, 1, -1},     // light from top-right-front
    {-1, 1, -0.5}  // light from top-left-back
};

// Initialising the bezier curve for the soccer ball
vec3_t soc_bezier_p0 = { -1.5, 0, -5 }; // start at left
vec3_t soc_bezier_p1 = { -1, 0, -5 };
vec3_t soc_bezier_p2 = { 1, 0, -5 };
vec3_t soc_bezier_p3 = { 1.5, 0, -5 };  // end at the right

// Initialising the bezier curve for the octahedron
vec3_t oct_bezier_p0 = {  1.5, 0, -5 };  // start at right
vec3_t oct_bezier_p1 = {  1, 0, -5 };
vec3_t oct_bezier_p2 = { -1, 0, -5};
vec3_t oct_bezier_p3 = { -1.5, 0, -5 };  // end at the left

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

                // checking  for duplicate edge
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

// Generate an octahedron using manually given vertex coordinates
void generate_octahedron(vec3_t** oct_vertices, int* oct_vcount, int (**oct_edges)[2], int* oct_ecount) {
    // Initialising number of edges, vertices
    *oct_vcount = 6;
    *oct_ecount = 12;

    // Allocating space for vertices and edges using malloc
    *oct_vertices = malloc(sizeof(vec3_t) * (*oct_vcount));
    *oct_edges = malloc(sizeof(int[2]) * (*oct_ecount));

    // Coordinates of the octahedron edges
    vec3_t octahedron_vertices[6] = {
        {  1,  0,  0 },
        { -1,  0,  0 },
        {  0,  1,  0 },
        {  0, -1,  0 },
        {  0,  0,  1 },
        {  0,  0, -1 }
    };

    // Edges of the octahedron (How the vertices are connected)
    int octahedron_edges[12][2] = {
        {0, 2}, {0, 3}, {0, 4}, {0, 5},
        {1, 2}, {1, 3}, {1, 4}, {1, 5},
        {2, 4}, {2, 5}, {3, 4}, {3, 5}
    };

    // Output the vertices
    for (int i = 0; i < *oct_vcount; i++) (*oct_vertices)[i] = octahedron_vertices[i];

    // Output the edges
    for (int i = 0; i < *oct_ecount; i++) {
        (*oct_edges)[i][0] = octahedron_edges[i][0]; // Starting point of the edge
        (*oct_edges)[i][1] = octahedron_edges[i][1]; // End point of the edge
    }
}

int main() {

    // For the soccer ball
    vec3_t* soccer_vertices = NULL;
    int soccer_vertex_count;
    int (*soccer_edges)[2] = NULL;
    int soccer_edge_count;

    // Load the soccer ball from object file
    if (!load_obj("build/soccer.obj", &soccer_vertices, &soccer_vertex_count, &soccer_edges, &soccer_edge_count)) return 1;

    // For the octahedron
    vec3_t* oct_vertices = NULL;
    int oct_vertex_count;
    int (*oct_edges)[2] = NULL;
    int oct_edge_count;

    // Generate the octahedron
    generate_octahedron(&oct_vertices, &oct_vertex_count, &oct_edges, &oct_edge_count);

    // Enter the loop
    for (int frame = 0; frame < FRAME_COUNT; frame++) {
        canvas_t *canvas = canvas_create(WIDTH, HEIGHT);
        if (!canvas) {
            fprintf(stderr, "Failed to create canvas.\n");
            return 1;
        }

        // Clear canvas
        for (size_t y = 0; y < HEIGHT; ++y)
            for (size_t x = 0; x < WIDTH; ++x)
                canvas->pixels[y][x] = 0.0f;

        float time = 2 * (float)frame / FRAME_COUNT;

        // Animate positions using Bezier curve
        vec3_t anim_pos_soc = vec3_bezier(soc_bezier_p0, soc_bezier_p1, soc_bezier_p2, soc_bezier_p3, time);
        vec3_t anim_pos_oct = vec3_bezier(oct_bezier_p0, oct_bezier_p1, oct_bezier_p2, oct_bezier_p3, time);

        // Appying Quaternion rotation
        quat_t q0 = quat_from_axis_angle((vec3_t){1, 0, 0}, 2.0f * ROTATION_MULTIPLIER);
        quat_t q1 = quat_from_axis_angle((vec3_t){0, 1, 0}, 2.0f * PI * ROTATION_MULTIPLIER);
        quat_t q = quat_slerp(q0, q1, time);
        mat4 rotate = quat_to_mat4(q);

        // Scaling the objects
        mat4 soc_scale = mat4_scale(0.4f, 0.4f, 0.4f);
        mat4 oct_scale = mat4_scale(2.0f, 2.0f, 2.0f);

        // Applying translations
        mat4 soc_translate = mat4_translate(anim_pos_soc.x, anim_pos_soc.y, anim_pos_soc.z);
        mat4 oct_translate = mat4_translate(anim_pos_oct.x, anim_pos_oct.y, anim_pos_oct.z);


        // Multiplying matrices to get the full transformation
        mat4 soc_model = mat4_mul(soc_translate, mat4_mul(rotate, soc_scale));
        mat4 oct_model = mat4_mul(oct_translate, mat4_mul(rotate, oct_scale));


        mat4 view = mat4_identity();
        mat4 proj = mat4_frustum_asymetric(-1.0, 1.0, -1.0, 1.0, 1.0f, 10.0f);
        mat4 soc_mvp = mat4_mul(proj, mat4_mul(view, soc_model));
        mat4 oct_mvp = mat4_mul(proj, mat4_mul(view, oct_model));

        // Projection of soccer ball
        vec3_t* soccer_projected = malloc(sizeof(vec3_t) * soccer_vertex_count);
        for (int i = 0; i < soccer_vertex_count; i++)
            soccer_projected[i] = project_vertex(soccer_vertices[i], soc_mvp, WIDTH, HEIGHT);

        for (int i = 0; i < soccer_edge_count; i++) {
            int idx0 = soccer_edges[i][0];
            int idx1 = soccer_edges[i][1];
            vec3_t p0 = soccer_projected[idx0];
            vec3_t p1 = soccer_projected[idx1];

            // Clipping the soccer ball to a circle
            if (clip_to_circular_viewport(canvas, p0.x, p0.y) &&
                clip_to_circular_viewport(canvas, p1.x, p1.y)) {
                float brightness = compute_multi_light_intensity(soccer_vertices[idx0], soccer_vertices[idx1], light_dirs, 2);
                draw_line_f(canvas, p0.x, p0.y, p1.x, p1.y, brightness);
            }
        }

        // Projection of octahedron
        vec3_t* oct_projected = malloc(sizeof(vec3_t) * oct_vertex_count);
        for (int i = 0; i < oct_vertex_count; i++)
            oct_projected[i] = project_vertex(oct_vertices[i], oct_mvp, WIDTH, HEIGHT);

        for (int i = 0; i < oct_edge_count; i++) {
            int idx0 = oct_edges[i][0];
            int idx1 = oct_edges[i][1];
            vec3_t p0 = oct_projected[idx0];
            vec3_t p1 = oct_projected[idx1];

            // Clipping the octahedron to a circle
            if (clip_to_circular_viewport(canvas, p0.x, p0.y) &&
                clip_to_circular_viewport(canvas, p1.x, p1.y)) {
                float brightness = compute_multi_light_intensity(oct_vertices[idx0], oct_vertices[idx1], light_dirs, 2);
                draw_line_f(canvas, p0.x, p0.y, p1.x, p1.y, brightness);
            }
        }

        // Saving each frame as a PGM file
        char filename[64];
        snprintf(filename, sizeof(filename), "build/frames/frame_%03d.pgm", frame);
        canvas_save_pgm(canvas, filename);
        printf("Saved frame: %s\n", filename);
    
        // Close the canvas and free the space
        canvas_destroy(canvas);
        free(soccer_projected);
        free(oct_projected);
    }

    // Free the memory
    free(soccer_vertices);
    free(soccer_edges);
    free(oct_vertices);
    free(oct_edges);
    
    return 0;
}

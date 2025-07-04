#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "../include/tiny3d.h"

#define WIDTH 800
#define HEIGHT 800
#define PI 3.14159265f
#define FRAME_COUNT 200
#define ZOOM_SCALE 500.0f

#define MAX_VERTICES 2048
#define MAX_FACES 4096

vec3_t light_dirs[] = {
    {1, 1, -1}, {-1, 1, -0.5}
};

vec3_t bezier_p0 = { -2.5, 0, -5 };
vec3_t bezier_p1 = { -1, 0, -5 };
vec3_t bezier_p2 = { 1, 0, -5 };
vec3_t bezier_p3 = { 2.5, 0, -5 };

// Load OBJ and extract unique edges from triangle faces
bool load_obj(const char* filename, vec3_t** out_vertices, int* out_vcount, int (**out_edges)[2], int* out_ecount) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Could not open %s\n", filename);
        return false;
    }

    vec3_t temp_vertices[MAX_VERTICES];
    int temp_faces[MAX_FACES][3];
    int vcount = 0, fcount = 0;

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == 'v' && line[1] == ' ') {
            vec3_t v;
            sscanf(line, "v %f %f %f", &v.x, &v.y, &v.z);
            temp_vertices[vcount++] = v;
        } else if (line[0] == 'f') {
            int i0, i1, i2;
            sscanf(line, "f %d %d %d", &i0, &i1, &i2);
            temp_faces[fcount][0] = i0 - 1;
            temp_faces[fcount][1] = i1 - 1;
            temp_faces[fcount][2] = i2 - 1;
            fcount++;
        }
    }
    fclose(file);

    *out_vertices = malloc(sizeof(vec3_t) * vcount);
    for (int i = 0; i < vcount; i++) (*out_vertices)[i] = temp_vertices[i];
    *out_vcount = vcount;

    int (*edges)[2] = malloc(sizeof(int[2]) * fcount * 3);
    int edge_count = 0;

    for (int i = 0; i < fcount; i++) {
        int a = temp_faces[i][0];
        int b = temp_faces[i][1];
        int c = temp_faces[i][2];
        int new_edges[3][2] = {{a,b},{b,c},{c,a}};
        for (int j = 0; j < 3; j++) {
            int exists = 0;
            for (int k = 0; k < edge_count; k++) {
                if ((edges[k][0] == new_edges[j][0] && edges[k][1] == new_edges[j][1]) ||
                    (edges[k][1] == new_edges[j][0] && edges[k][0] == new_edges[j][1])) {
                    exists = 1;
                    break;
                }
            }
            if (!exists) {
                edges[edge_count][0] = new_edges[j][0];
                edges[edge_count][1] = new_edges[j][1];
                edge_count++;
            }
        }
    }

    *out_edges = realloc(edges, sizeof(int[2]) * edge_count);
    *out_ecount = edge_count;
    return true;
}

vec3_t project_vertex(vec3_t vertex, mat4 mvp, int screen_width, int screen_height) {
    vec4_t v4 = {vertex.x, vertex.y, vertex.z, 1.0f};
    vec4_t projected = mat4_mul_vec4(mvp, v4);

    if (projected.w == 0.0f) projected.w = 1e-6f;
    projected.x /= projected.w;
    projected.y /= projected.w;
    projected.z /= projected.w;

    vec3_t screen_pos;
    screen_pos.x = (projected.x * 0.5f + 0.5f) * screen_width;
    screen_pos.y = (1.0f - (projected.y * 0.5f + 0.5f)) * screen_height;
    screen_pos.z = projected.z;

    return screen_pos;
}

int main() {
    vec3_t* vertices = NULL;
    int vertex_count;
    int (*edges)[2] = NULL;
    int edge_count;

    if (!load_obj("soccer.obj", &vertices, &vertex_count, &edges, &edge_count)) return 1;

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

        float time = (float)frame / FRAME_COUNT;

        // Animate position using Bezier curve
        vec3_t anim_pos = vec3_bezier(bezier_p0, bezier_p1, bezier_p2, bezier_p3, time);

        // Quaternion rotation
        quat_t q0 = quat_from_axis_angle((vec3_t){0, 1, 0}, 0.0f);
        quat_t q1 = quat_from_axis_angle((vec3_t){0, 1, 0}, 2.0f * PI);
        quat_t q = quat_slerp(q0, q1, time);
        mat4 rotate = quat_to_mat4(q);

        mat4 scale = mat4_scale(1.5f, 1.5f, 1.5f);
        mat4 translate = mat4_translate(anim_pos.x, anim_pos.y, anim_pos.z);
        mat4 model = mat4_mul(translate, mat4_mul(rotate, scale));

        mat4 view = mat4_identity();
        mat4 proj = mat4_frustum_asymetric(-1, 1, -1, 1, 1.0f, 10.0f);
        mat4 mvp = mat4_mul(proj, mat4_mul(view, model));

        vec3_t* projected = malloc(sizeof(vec3_t) * vertex_count);
        for (int i = 0; i < vertex_count; i++)
            projected[i] = project_vertex(vertices[i], mvp, WIDTH, HEIGHT);

        for (int i = 0; i < edge_count; i++) {
            int idx0 = edges[i][0];
            int idx1 = edges[i][1];
            vec3_t p0 = projected[idx0];
            vec3_t p1 = projected[idx1];

            if (clip_to_circular_viewport(canvas, p0.x, p0.y) &&
                clip_to_circular_viewport(canvas, p1.x, p1.y)) {
                float brightness = compute_multi_light_intensity(vertices[idx0], vertices[idx1], light_dirs, 2);
                draw_line_f(canvas, p0.x, p0.y, p1.x, p1.y, brightness);
            }
        }

        char filename[64];
        snprintf(filename, sizeof(filename), "build/frames/frame_%03d.pgm", frame);
        canvas_save_pgm(canvas, filename);
        printf("Saved frame: %s\n", filename);

        canvas_destroy(canvas);
        free(projected);
    }

    free(vertices);
    free(edges);
    return 0;
}

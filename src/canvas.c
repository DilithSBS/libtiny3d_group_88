#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/canvas.h"

canvas_t *canvas_create(size_t width, size_t height) {
    canvas_t *canvas = malloc(sizeof(canvas_t));
    if (!canvas) return NULL;

    canvas->width = width;
    canvas->height = height;

    canvas->pixels = malloc(height * sizeof(float*));
    if (!canvas->pixels) {
        free(canvas);
        return NULL;
    }

    for (size_t y = 0; y < height; y++) {
        canvas->pixels[y] = calloc(width, sizeof(float)); // initialized to 0.0
        if (!canvas->pixels[y]) {
            for (size_t j = 0; j < y; j++) free(canvas->pixels[j]);
            free(canvas->pixels);
            free(canvas);
            return NULL;
        }
    }

    return canvas;
}

void canvas_destroy(canvas_t* canvas) {
    if (!canvas) return;
    for (size_t y = 0; y < canvas->height; y++) {
        free(canvas->pixels[y]);
    }
    free(canvas->pixels);
    free(canvas);
}

// Clamp helper
static float clamp(float value, float min, float max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

void set_pixel_f(canvas_t* canvas, float x, float y, float intensity) {
    if (!canvas) return;

    int x0 = (int)floorf(x);
    int y0 = (int)floorf(y);
    float dx = x - x0;
    float dy = y - y0;

    float w00 = (1 - dx) * (1 - dy);
    float w10 = dx * (1 - dy);
    float w01 = (1 - dx) * dy;
    float w11 = dx * dy;

    if (x0 >= 0 && y0 >= 0 && x0 < (int)canvas->width && y0 < (int)canvas->height)
        canvas->pixels[y0][x0] += w00 * intensity;

    if (x0 + 1 >= 0 && y0 >= 0 && x0 + 1 < (int)canvas->width && y0 < (int)canvas->height)
        canvas->pixels[y0][x0 + 1] += w10 * intensity;

    if (x0 >= 0 && y0 + 1 >= 0 && x0 < (int)canvas->width && y0 + 1 < (int)canvas->height)
        canvas->pixels[y0 + 1][x0] += w01 * intensity;

    if (x0 + 1 >= 0 && y0 + 1 >= 0 && x0 + 1 < (int)canvas->width && y0 + 1 < (int)canvas->height)
        canvas->pixels[y0 + 1][x0 + 1] += w11 * intensity;
}

void draw_line_f(canvas_t* canvas, float x0, float y0, float x1, float y1, float thickness) {
    if (!canvas) return;

    float dx = x1 - x0;
    float dy = y1 - y0;
    float length = sqrtf(dx * dx + dy * dy);

    if (length == 0.0f) return;

    float step_x = dx / length;
    float step_y = dy / length;

    float tx = -step_y;  // perpendicular unit vector x
    float ty = step_x;   // perpendicular unit vector y

    for (float i = 0; i < length; i += 0.5f) {
        float px = x0 + step_x * i;
        float py = y0 + step_y * i;

        // draw thickness by drawing perpendicular mini-lines
        for (float t = -thickness / 2.0f; t <= thickness / 2.0f; t += 0.5f) {
            float fx = px + tx * t;
            float fy = py + ty * t;
            set_pixel_f(canvas, fx, fy, 1.0f);
        }
    }
}

#include <stdio.h>     // ✅ defines FILE, fopen, fprintf, etc.
#include <stdlib.h>
#include <math.h>
#include "canvas.h"

#define PI 3.14159265f

// Simple function to clear the canvas to a given brightness
void canvas_clear(canvas_t* canvas, float value) {
    for (size_t y = 0; y < canvas->height; y++) {
        for (size_t x = 0; x < canvas->width; x++) {
            canvas->pixels[y][x] = value;
        }
    }
}

// Simple function to save the canvas to a grayscale .pgm file
void canvas_save_pgm(const canvas_t* canvas, const char* filename) {
    FILE* f = fopen(filename, "w");  // ✅ FILE is defined in stdio.h
    if (!f) {
        printf("Error: couldn't open file for writing\n");
        return;
    }

    fprintf(f, "P2\n%zu %zu\n255\n", canvas->width, canvas->height);
    for (size_t y = 0; y < canvas->height; y++) {
        for (size_t x = 0; x < canvas->width; x++) {
            int val = (int)(255.0f * canvas->pixels[y][x]);
            if (val > 255) val = 255;
            fprintf(f, "%d ", val);
        }
        fprintf(f, "\n");
    }
    fclose(f);
}

int main() {
    canvas_t* canvas = canvas_create(512, 512);
    if (!canvas) return 1;

    canvas_clear(canvas, 0.0f);  // fill with black

    float cx = canvas->width / 2.0f;
    float cy = canvas->height / 2.0f;
    float radius = 200.0f;

    // Create brush
    brush_t brush;
    brush.thickness = 2.5f;
    brush.intensity = 1.0f;

    // Draw 24 lines from center like a clock
    for (int deg = 0; deg < 360; deg += 15) {
        float angle = deg * (PI / 180.0f);
        float x = cx + radius * cosf(angle);
        float y = cy + radius * sinf(angle);
        draw_line_f(canvas, cx, cy, x, y, &brush);
    }

    canvas_save_pgm(canvas, "output_3.pgm");
    canvas_destroy(canvas);
    return 0;
}

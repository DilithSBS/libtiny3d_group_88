#ifndef CANVAS_H
#define CANVAS_H

#include <stddef.h> // for size_t

// Define the canvas structure
typedef struct {
    size_t width;
    size_t height;
    float** pixels;  // 2D array: pixels[y][x]
} canvas_t;

// Create and destroy canvas
canvas_t *canvas_create(size_t width, size_t height);
void canvas_destroy(canvas_t* canvas);

// Set a pixel with floating-point coordinates and intensity
void set_pixel_f(canvas_t* canvas, float x, float y, float intensity);

// Draw a floating-point line with thickness using DDA
void draw_line_f(canvas_t* canvas, float x0, float y0, float x1, float y1, float thickness);

#endif // CANVAS_H

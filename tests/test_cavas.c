#include <math.h>
#include "../include/tiny3d.h"

#define PI 3.14159265f

int main() {
    size_t width = 1600, height = 1600;
    canvas_t *canvas = canvas_create(width, height);

    float x_center = width / 2.0f;
    float y_center = height / 2.0f;
    float radius = 350.0f;

    // Drawing 24 lines starting from the center
    for (int deg = 0; deg < 360; deg += 15) {
        float rad = deg * (PI / 180.0f);
        float x = x_center + radius * cosf(rad);
        float y = y_center + radius * sinf(rad);
        draw_line_f(canvas, x_center, y_center, x, y, 4.0f);
    }

    // // Drawing lines from (0,0)
    // for (int deg = 0; deg < 90; deg += 5) {
    //     float rad = deg * (PI / 180.0f);
    //     float x = radius * cosf(rad);
    //     float y = radius * sinf(rad);
    //     draw_line_f(canvas, 0, 0, x, y, 1.5f);

    // }

    // // Drawing lines from (width, height)
    // for (int deg = 0; deg < 90; deg += 5) {
    //     float rad = deg * (PI / 180.0f);
    //     float x = width - radius * cosf(rad);
    //     float y = height - radius * sinf(rad);
    //     draw_line_f(canvas, width, height, x, y, 1.5f);
        
    // }

    // Write the canvas to a PGM image file
    canvas_save_pgm(canvas, "tests/visual_tests/test_canvas/test_canvas.pgm");

    // Destroy the canvas
    canvas_destroy(canvas);

    return 0;
}

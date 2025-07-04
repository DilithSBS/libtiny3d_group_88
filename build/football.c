// C program for the above approach

#include <conio.h>
#include <graphics.h>
#include <stdio.h>

// Driver Code
void main()
{
    int gd = DETECT, gm;

    // Initialize of gdriver with
    // DETECT macros
    initgraph(&gd, &gm, "C:\\turboc3\\bgi");

    // Ground Outline
    rectangle(100, 50, 1200, 550);

    // Coloring Green
    setfillstyle(SOLID_FILL, GREEN);
    floodfill(150, 150, 15);

    // Ground Middle Line
    line(650, 50, 650, 550);
    line(656, 50, 656, 550);

    // Coloring White
    setfillstyle(SOLID_FILL, WHITE);
    floodfill(652, 150, 15);

    // Mid Circles
    circle(653, 300, 60);
    circle(653, 300, 65);
    circle(653, 300, 10);

    // Outer Rectangle Left
    rectangle(100, 200, 250, 400);
    rectangle(100, 205, 245, 395);

    // Inner Rectangle Left
    rectangle(100, 230, 200, 370);
    rectangle(100, 235, 195, 365);

    // Arc Left Side
    arc(250, 300, 270, 90, 40);
    arc(250, 300, 270, 90, 35);

    // Outer Rectangle Right
    rectangle(1200, 200, 1050, 400);
    rectangle(1200, 205, 1055, 395);

    // Inner Rectangle Right
    rectangle(1200, 230, 1100, 370);
    rectangle(1200, 235, 1105, 365);

    // Arc Right Side
    arc(1051, 300, 90, 270, 40);
    arc(1051, 300, 90, 270, 35);

    // Coloring All White
    floodfill(714, 300, 15);
    floodfill(592, 300, 15);
    floodfill(657, 300, 15);
    floodfill(645, 300, 15);
    floodfill(247, 300, 15);
    floodfill(197, 300, 15);
    floodfill(287, 300, 15);
    floodfill(1053, 300, 15);
    floodfill(1103, 300, 15);
    floodfill(1013, 300, 15);

    // Holding Screen For a While
    getch();

    // Close the initialized gdriver
    closegraph();
}
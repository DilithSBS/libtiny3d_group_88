# libtiny3d
## 3D Software Renderer Library
### CO1020 - C Project - E/23 - Semester 2
_________________________________________________________________________
### Created by 
        Group 88
        E/23/336  -  S.M.D.S.B. Samarakoon  -  e23336@eng.pdn.ac.lk
        E/23/117  -  W.R.A.D.N. Gunathilake -  e23117@eng.pdn.ac.lk
_________________________________________________________________________

### File System Structure
    libtiny3d/
    ├── include/ # Header files
    │ ├── canvas.h
    │ ├── math3d.h
    │ ├── renderer.h
    │ ├── lighting.h
    │ └── tiny3d.h
    │ 
    ├── src/ # Source files
    │ ├── canvas.c
    │ ├── math3d.c
    │ ├── renderer.c
    │ └── lighting.c
    │ 
    ├── tests/ # Test and visualization scripts
    │ ├── visual_tests/
    │ │ ├── test_canvas/
    │ │ │ ├── test_canvas.pgm
    │ │ │ └── test_canvas.png 
    │ │ │ 
    │ │ ├── test_math/
    │ │ │ ├── frame_*_*_*.pgm
    │ │ │ └── frame_*_*_*.png 
    │ │ │
    │ │ └── test_pipeline/
    │ │   ├── test_pipeline_*.pgm
    │ │   ├── test_pipeline.gif
    │ │   └── test_pipeline.mp4
    │ │ 
    │ ├── soccer.obj
    │ ├── test_canvas.c
    │ ├── test_math.c
    │ └── test_pipeline.c
    │ 
    ├── demo/ # Main demo showing full rendering
    │ └── main.c
    │ 
    ├── build/ # Output directory
    │ ├── canvas.o
    │ ├── math3d.o
    │ ├── renderer.o
    │ ├── lighting.o
    │ ├── libtuny3d.a
    │ ├── demo
    │ └── frames/
    │   ├── frames_*.pgm
    │   ├── main.mp4
    │   └── main.gif
    │
    ├── documentation/ # Report and references
    │ ├── Group88_project.mp4
    │ └── Group88_report.pdf
    │ 
    ├── Makefile
    ├── demo_gif_mp4.py
    ├── test_canvas_png.py
    ├── test_math_png.py
    ├── test_pipeline_gif_mp4.py
    ├── soccer.obj
    └── README.md
_________________________________________________________________________

## Build Instructions

Follow the steps below to build and run the `libtiny3d` 3D graphics engine.

### Prerequisites

Make sure your system has the following installed:

- GCC (GNU Compiler Collection)
- Make
- ImageMagick — to convert `.pgm` files to `.png`
- imageio, numpy, matplotlib, PIL python libraries (Optional) to convert `.pgm` files to `.png`

They can be installed using:

```bash
sudo apt update
sudo apt install build-essential imagemagick
pip install imageio numpy matplotlib, pillow
```
_________________________________________________________________________
## Build
In the root of the project run the command:
```bash
make
```
_________________________________________________________________________

## Run
### Demo
Run this command in terminal
```bash
./build/demo
```

This will output 200 PGM frames like:
```bash
build/frames/frame_*.pgm
```
### Canvas test
```bash
./tests/test_canvas
```
This will output a PGM frame like:
```bash
build/visual_tests/test_canvas/test_canvas.pgm
```
### Math test
```bash
./tests/test_math
```
This will output a PGM frame like:
```bash
build/visual_tests/test_math/frame_*_*_*.pgm
```
### Pipeline test
```bash
./tests/test_pipeline
```
This will output PGM frames like:
```bash
build/visual_tests/test_pipeline/test_pipeline_*.pgm
```
_________________________________________________________________________

## View Output of the Demo 
Generate `.mp4` and `.gif` files to view the output.

### Using python
Using the python program we created:
in the root of the project:
Run
```bash
python demo_gif_mp4.py
```
The `.mp4` and `.gif` files will be generated like:
```bash
build/main.gif
build/main.mp4
```
## VIew the output of the tests
Generate `.mp4` and `.gif` files to view the output using the python program we created:

### Canvas test
in the root of the project:
Run
```bash
python test_canvas_png.py
```
The `.png` file will be generated like:
```bash
tests/visual_tests/test_canvas/test_canvas.png
```
### Math test
in the root of the project:
Run
```bash
python test_math_png.py
```
The `.png` file will be generated like:
```bash
tests/visual_tests/test_math/test_math.png
```
### Pipeline test
Using the python program we created:
in the root of the project:
Run
```bash
python test_pipeline_gif_mp4.py
```
The `.mp4` and `.gif` files will be generated like:
```bash
tests/visual_tests/test_pipeline/test_pipeline.gif
tests/visual_tests/test_pipeline/test_pipeline.mp4
```
_________________________________________________________________________

## Clean Build
```bash
make clean
```
_________________________________________________________________________

## Features
### Task 1: Canvas & Line Drawing
- Floating-point precision canvas
- Smooth DDA-based line drawing
- Bilinear intensity blending

### Task 2: 3D Math Foundation
- Vector and matrix structures
- Spherical-Cartesian conversions
- Quaternion rotation and SLERP
- Matrix transforms (translate, scale, rotate, frustum)

### Task 3: Rendering Pipeline
- 3D to 2D projection
- Circular viewport clipping
- Depth-sorted wireframe rendering
- Quaternion rotations to avoid rotation bugs like Gimbal lock
- Soccer ball wireframe (truncated icosahedron)

### Task 4: Lighting & Animation
- Lambertian lighting based on direction
- Smooth object animation with Bézier curves
- Soccer ball and an Octahedron moving in sync
___
## Demo Output
The output `.gif` and `.mp4` files demonstrate:
- Line precision and thickness of the wireframes
- 3D transforms of a octahedron and a soccer ball on the canvas
- Lighting and Bézier animations applied in the movements of the objects
_________________________________________________________________________

## AI Tool Usage
ChatGPT was used as helping agent for:
- Making header files accurately.
- Clarifying mathematical logics
- Making a soccer ball out of an object file
- Debugging codes
- Structuring code

Since we did not have any knowledge about 3D transformations and pixel manipulation, we had to use AI a lot. But as we worked on this project, now we have a good understanding about concepts like **Bilinear Filtering, DDA Algorithm, Quaternion rotations, Bezier Curves, Lambert lighting**

Final implementation and testing were done manually by us with full understanding.

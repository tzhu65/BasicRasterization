== Basic Rasterization == 

Tony Zhu
Programming Assignment 2
COMP 575/770
March 23, 2016

Platform: Macbook Pro OS X El Capitan
Runtimes:
	Intersection ~ 0.14s
	Flat shading ~ 0.14s
	Gouraud shading ~ 0.20s
	Phong shading ~ 0.34s

== Compilation Instructions ==

Libraries:
	- Eigen

(1) Get brew (mac package manager) - http://brew.sh/

(2) Install Eigen with
brew install eigen

(3) Check if it was installed to /usr/local/include/eigen3/

(a) If so, then try running the program in Xcode

(b) Otherwise, in the build settings, change the custom compiler flags, under “Other C++ Flags”, to -I /your/path/to/eigen/. Then the program should be able to compile.

(4) Enter the type of image through stdin
	0 - Intersection
	1 - Flat shading
	2 - Gouraud saying
	3 - Phong shading

== Program description ==

The entire rasterization pipeline is written in main.cpp
All the transformation matrices are initialized along with the scene in the generateImage function. Lights are first transformed, and then each object is rendered one at a time.

In the vertex stage (vertexStage function), all vertices are transformed to screen space, but if intermediate results are needed (for shading), those will be stored.

For rasterization, the z value was not calculated for each pixel (not needed for this case), and instead the average of the vertices on each triangle was used instead for the z-buffer. The dot product edge test was used to see if a pixel was inside the triangle. The conservative super of pixels visited was simply the rectangle bounded  by the max/min x/y values of the triangle. After confirming that the pixel should be drawn, the pixel was added to the buffer. Barycentric coordinates were used for Gouraud shading (interpolated colors) and Phong shading (interpolated normals).





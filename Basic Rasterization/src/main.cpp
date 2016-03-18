//
//  main.cpp
//  Basic Rasterization
//
//  Created by Tony Zhu on 3/18/16.
//  Copyright © 2016 Tony Zhu. All rights reserved.
//

#include <ctime>
#include <iostream>
#include <OpenGl/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>
#include <math.h>
#include <Eigen/Dense>

#include "camera.h"
#include "perspective.h"
#include "viewport.h"
#include "transformer.h"

#include "sphere.h"
#include "light.h"
#include "scene.h"

using namespace Eigen;

// Type of rendering
int IMAGE_TYPE = 3;

//  Camera settings
int VIEWPORT_WIDTH = 512;
int VIEWPORT_HEIGHT = 512;

float PERSPECTIVE_L = -0.1f;
float PERSPECTIVE_R =  0.1f;
float PERSPECTIVE_B = -0.1f;
float PERSPECTIVE_T =  0.1f;
float PERSPECTIVE_N = -0.1f;
float PERSPECTIVE_F = -1000.0f;

Vector3f CAMERA_U(1.0f, 0.0f, 0.0f);
Vector3f CAMERA_V(0.0f, 1.0f, 0.0f);
Vector3f CAMERA_W(0.0f, 0.0f, 1.0f);
Vector3f CAMERA_E(0.0f, 0.0f, 0.0f);

float LIGHT_INTENSITY = 0.2;
float GAMMA_CORRECTION = 2.2;

// Create the scene
Scene* generateScene() {
    Scene* s = new Scene();
    s->light_intensity_ = LIGHT_INTENSITY;
    
    // Surfaces
    Sphere* s1 = new Sphere(-4.0f, 0.0f, -7.0f, 1.0f);
    Sphere* s2 = new Sphere(-0.0f, 0.0f, -7.0f, 2.0f);
    Sphere* s3 = new Sphere( 4.0f, 0.0f, -7.0f, 1.0f);
    
    s1->material_.ka_ << 1.0f, 0.0f, 0.0f;
    s1->material_.kd_ << 1.0f, 0.0f, 0.0f;
    s1->material_.ks_ << 0.0f, 0.0f, 0.0f;
    s1->material_.spower_ = 0;
    
    s2->material_.ka_ << 0.0f, 1.0f, 0.0f;
    s2->material_.kd_ << 0.0f, 0.5f, 0.0f;
    s2->material_.ks_ << 0.5f, 0.5f, 0.5f;
    s2->material_.spower_ = 32;
    
    s3->material_.ka_ << 0.0f, 0.0f, 1.0f;
    s3->material_.kd_ << 0.0f, 0.0f, 1.0f;
    s3->material_.ks_ << 0.0f, 0.0f, 0.0f;
    s3->material_.spower_ = 0;
    
//    s->addSurface(s1);
    s->addSurface(s2);
//    s->addSurface(s3);
    
    Light* l1 = new Light(-4.0f, 4.0f, -3.0f);
    Light* l2 = new Light( 4.0f, 4.0f, -3.0f);

    l1->color_ << 1.0f, 1.0f, 1.0f;
    l2->color_ << 1.0f, 0.0f, 0.0f;
    
    s->addLight(l1);
//    s->addLight(l2);
    
    return s;
}

// Gamma correction
Vector3f gammaCorrect(Vector3f c ) {
    c << pow(c(0), 1.0f / GAMMA_CORRECTION),
    pow(c(1), 1.0f / GAMMA_CORRECTION),
    pow(c(2), 1.0f / GAMMA_CORRECTION);
    return c;
}

// Vertex stage
void vertexStage(Surface &s, Transformer &t, Vector3f triangleColoring[], Scene &scene) {
    
    // Convert to eye space
    Vector4f point;
    for (int i = 0; i < s.gNumVertices_; i++) {
        point << s.vertices_[i].p_(0), s.vertices_[i].p_(1), s.vertices_[i].p_(2), 1.0f;
        point = t.c_.camera_ * s.transform_ * point;
        s.vertices_[i].p_ << point(0), point(1), point(2);
        s.vertices_[i].eye_p_ << point(0), point(1), point(2);
    }
    
    // Flat shading
    if (IMAGE_TYPE == 1) {
        for (int i = 0; i < s.gNumTriangles_; i++) {
            Vector3f v0 = s.vertices_[s.gIndexBuffer_[3 * i + 0]].p_;
            Vector3f v1 = s.vertices_[s.gIndexBuffer_[3 * i + 1]].p_;
            Vector3f v2 = s.vertices_[s.gIndexBuffer_[3 * i + 2]].p_;
            Vector3f m = (v0 + v1 + v2) / 3.0;
            Vector3f n = (v1 - v0).cross(v2 - v0);
            n.normalize();
            Vector3f c = scene.calculateColor(s, n, m);
            triangleColoring[i] = gammaCorrect(c);
        }
    }
    
    // Gouraud shading
    else if (IMAGE_TYPE == 2) {
        for (int i = 0; i < s.gNumVertices_; i++) {
            Vertex vertex = s.vertices_[i];
            Vector3f color(0.0f, 0.0f, 0.0f);
            
            Vector3f n;
            n = s.calculateNormal(vertex.p_, t.c_.camera_);
            s.vertices_[i].color_ = gammaCorrect(scene.calculateColor(s, n, vertex.p_));
        }
    }
    
    // Phong shading
    else if (IMAGE_TYPE == 3) {
        // Store calculated normals
        for (int i = 0; i < s.gNumVertices_; i++) {
            Vertex vertex = s.vertices_[i];
            Vector3f n = s.calculateNormal(vertex.p_, t.c_.camera_);
            s.vertices_[i].normal_ = n;
        }
    }
    
    // Convert to screen space
    for (int i = 0; i < s.gNumVertices_; i++) {
        point << s.vertices_[i].p_(0), s.vertices_[i].p_(1), s.vertices_[i].p_(2), 1.0f;
        point = t.p_.perspective_ * point;
        point = point / point(3);
        point = t.v_.viewport_ * t.p_.ortho_ * point;
        s.vertices_[i].p_ << point(0), point(1), point(2);
    }
}

// Rasterizer stage
void rasterizer(Surface &s, Transformer &t, float pixels[], float z_buffer[], Vector3f triangleColoring[], Scene &scene) {
    for (int i = 0; i < s.gNumTriangles_; i++) {
        Vertex vertex0 = s.vertices_[s.gIndexBuffer_[3 * i + 0]];
        Vertex vertex1 = s.vertices_[s.gIndexBuffer_[3 * i + 1]];
        Vertex vertex2 = s.vertices_[s.gIndexBuffer_[3 * i + 2]];
        
        Vector3f v0 = vertex0.p_;
        Vector3f v1 = vertex1.p_;
        Vector3f v2 = vertex2.p_;
        
        // Get the z value
        float z = ((v0 + v1 + v2) / 3.0f)(2);
        
        Vector2f a(v0(0), v0(1));
        Vector2f b(v1(0), v1(1));
        Vector2f c(v2(0), v2(1));
        
        Matrix2f perpendicular;
        perpendicular << 0, -1, 1, 0;
        Vector2f baP = perpendicular * (b - a);
        Vector2f cbP = perpendicular * (c - b);
        Vector2f acP = perpendicular * (a - c);

        
        // Visit conservative superset
        int maxX = std::max(a(0), std::max(b(0), c(0)));
        int minX = std::min(a(0), std::min(b(0), c(0)));
        int maxY = std::max(a(1), std::max(b(1), c(1)));
        int minY = std::min(a(1), std::min(b(1), c(1)));

        Vector2f p;
        for (int x = minX - 1; x < maxX + 1; x++) {
            for (int y = minY - 1; y < maxY + 1; y++) {
                p << x, y;
                
                // Edge test
                if ((p - a).dot(baP) > 0 &&
                    (p - b).dot(cbP) > 0 &&
                    (p - c).dot(acP) > 0) {
                
                    // Fragmentation stage
                    
                    // Check the z-buffer
                    if (z > z_buffer[t.v_.width_ * y + x]) {
                        z_buffer[t.v_.width_ * y + x] = z;
                        Vector3f color;
                        
                        // Intersection
                        if (IMAGE_TYPE == 0) {
                            color << 1.0f, 1.0f, 1.0f;
                        }
                        
                        // Flat shading
                        else if (IMAGE_TYPE == 1) {
                            color << triangleColoring[i](0),
                                     triangleColoring[i](1),
                                     triangleColoring[i](2);
                        }
                        
                        if (IMAGE_TYPE > 1) {
                            
                            // Solve for barycentric coordinates
                            Vector2f e0 = b - a;
                            Vector2f e1 = c - a;
                            Vector2f e2 = p - a;
                            float d00 = e0.dot(e0);
                            float d01 = e0.dot(e1);
                            float d11 = e1.dot(e1);
                            float d20 = e2.dot(e0);
                            float d21 = e2.dot(e1);
                            float denom = d00 * d11 - d01 * d01;
                            float v = (d11 * d20 - d01 * d21) / denom;
                            float w = (d00 * d21 - d01 * d20) / denom;
                            float u = 1.0f - v - w;
                            
                            // Gouraud shading
                            if (IMAGE_TYPE == 2) {

                                // Interpolate colors
                                Vector3f c0 = vertex0.color_;
                                Vector3f c1 = vertex1.color_;
                                Vector3f c2 = vertex2.color_;
                                color = (u*c0) + (v*c1) + (w*c2);
                            }
                            
                            // Phong shading
                            else if (IMAGE_TYPE == 3) {
                                
                                // Interpolate normal
                                Vector3f n;
                                Vector3f n0 = vertex0.normal_;
                                Vector3f n1 = vertex1.normal_;
                                Vector3f n2 = vertex2.normal_;
                                n = (u*n0) + (v*n1) + (w*n2);
                                n.normalize();

                                // Interpolate x, y, z point
                                Vector3f vp0 = vertex0.eye_p_;
                                Vector3f vp1 = vertex1.eye_p_;
                                Vector3f vp2 = vertex2.eye_p_;
                                Vector3f point = (u*vp0) + (v*vp1) + (w*vp2);
                                
                                color = gammaCorrect(scene.calculateColor(s, n, point));
                            }
                        }
                        pixels[4 * (t.v_.width_ * y + x) + 0] = color(0);
                        pixels[4 * (t.v_.width_ * y + x) + 1] = color(1);
                        pixels[4 * (t.v_.width_ * y + x) + 2] = color(2);
                    }
                }
            }
        }
    }
}

// Rendering pipeline
void renderSurface(Surface &s, Transformer &t, float pixels[], float z_buffer[], Scene &scene) {
    Vector3f* triangleColoring = new Vector3f[s.gNumTriangles_];
    
    // Vertex stage
    clock_t begin = clock();
    
    vertexStage(s, t, triangleColoring, scene);
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Vertex stage time: " << elapsed_secs << "s" << std::endl;
    
    
    // Rasterizer stage
    begin = clock();
    rasterizer(s, t, pixels, z_buffer, triangleColoring, scene);
    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Rasterizer time: " << elapsed_secs << "s" << std::endl;
    
    delete triangleColoring;
}


// Image calculation
void generateImage() {
    clock_t begin = clock();
    
    // Initialize the transformations
    Camera c = (Camera(CAMERA_U, CAMERA_V, CAMERA_W, CAMERA_E));
    Perspective p = Perspective(PERSPECTIVE_L,
                                PERSPECTIVE_R,
                                PERSPECTIVE_B,
                                PERSPECTIVE_T,
                                PERSPECTIVE_N,
                                PERSPECTIVE_F);
    Viewport v = Viewport(VIEWPORT_WIDTH, VIEWPORT_HEIGHT);
    Transformer transformer = Transformer(c, p, v);
    
    // Initialize background to black
    float pixels[v.height_ * v.width_ * 4];
    for (int y = 0; y < v.height_; y++) {
        for (int x = 0; x < v.width_; x++) {
            pixels[4 * (v.width_ * y + x) + 0] = 0.0f;
            pixels[4 * (v.width_ * y + x) + 1] = 0.0f;
            pixels[4 * (v.width_ * y + x) + 2] = 0.0f;
            pixels[4 * (v.width_ * y + x) + 3] = 1.0f;
        }
    }
    
    // Generate the z buffer
    float z_buffer[v.height_ * v.width_];
    for (int y = 0; y < v.height_; y++) {
        for (int x = 0; x < v.width_; x++) {
            z_buffer[y * v.width_ + x] = std::numeric_limits<float>::lowest();
        }
    }
    
    // Create the scene
    Scene scene = *generateScene();
    
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Initialization time: " << elapsed_secs << "s" << std::endl;
    
    // Render the surfaces through the pipeline
    begin = clock();
    
    // Transform lights
    for (int i = 0; i < scene.light_count_; i++) {
        Vector4f point;
        Light l = *scene.light_list_[i];
        point << l.position_(0), l.position_(1), l.position_(2), 1.0f;
        point = transformer.c_.camera_ * point;
        Vector3f lightp(point(0), point(1), point(2));
        scene.light_list_[i]->tposition_ = lightp;
    }
    
    for (int i = 0; i < scene.surface_count_; i++) {
        Surface& s = *scene.surface_list_[i];
        renderSurface(s, transformer, pixels, z_buffer, scene);
    }
    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Rendering pipeline time: " << elapsed_secs << "s" << std::endl;
    
    
    begin = clock();
    glDrawPixels(v.width_, v.height_, GL_RGBA, GL_FLOAT, pixels);
    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Draw pixels time: " << elapsed_secs << "s" << std::endl;
}

// GLUT display
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
    // Time the image generation time
    clock_t begin = clock();
    generateImage();
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Total image generation time: " << elapsed_secs << "s" <<std::endl;
    
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    std::cout << "Enter type of image" << std::endl;
    std::cin >> IMAGE_TYPE;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(VIEWPORT_WIDTH, VIEWPORT_HEIGHT);
    glutCreateWindow("PA2");
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}

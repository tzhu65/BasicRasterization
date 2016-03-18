//
//  sphere.cpp
//  Basic Rasterization
//
//  Created by Tony Zhu on 3/18/16.
//  Copyright © 2016 Tony Zhu. All rights reserved.
//

#include <Eigen/Dense>
#include "sphere.h"
#include "vertex.h"

Sphere::Sphere() {
    position_ << 0.0f, 0.0f, 0.0f;
    radius_ = 1.0f;
    createTriangles(32, 16);
    updateTransformMatrix();
}

Sphere::Sphere(float x, float y, float z, float r) {
    position_ << x, y, z;
    radius_ = r;
    createTriangles(32, 16);
    updateTransformMatrix();
}

void Sphere::updateTransformMatrix() {
    transform_ << radius_, 0.0f, 0.0f, position_(0),
    0.0f, radius_, 0.0f, position_(1),
    0.0f, 0.0f, radius_, position_(2),
    0.0f, 0.0f, 0.0f, 1.0f;
}

void Sphere::createTriangles(int width, int height) {
    
    float theta, phi;
    int t;
    
    gNumVertices_    = (height - 2) * width + 2;
    gNumTriangles_   = (height - 2) * (width - 1) * 2;
    gIndexBuffer_    = new int[3*gNumTriangles_];
    vertices_        = new Vertex[gNumVertices_];
    
    t = 0;
    for (int j = 1; j < height-1; ++j)
    {
        for (int i = 0; i < width; ++i)
        {
            theta = (float) j / (height-1) * M_PI;
            phi   = (float) i / (width-1)  * M_PI * 2;
            
            float   x   = sinf(theta) * cosf(phi);
            float   y   = cosf(theta);
            float   z   = -sinf(theta) * sinf(phi);
            
            vertices_[t] = Vertex(x, y, z);
            t++;
        }
    }
    
    vertices_[t] = Vertex(0.0f, 1.0f, 0.0f);
    t++;
    
    vertices_[t] = Vertex(0.0f, -1.0f, 0.0f);
    t++;
    
    t = 0;
    for (int j = 0; j < height-3; ++j)
    {
        for (int i = 0; i < width-1; ++i)
        {
            gIndexBuffer_[t++] = j*width + i;
            gIndexBuffer_[t++] = (j+1)*width + (i+1);
            gIndexBuffer_[t++] = j*width + (i+1);
            gIndexBuffer_[t++] = j*width + i;
            gIndexBuffer_[t++] = (j+1)*width + i;
            gIndexBuffer_[t++] = (j+1)*width + (i+1);
        }
    }
    for (int i = 0; i < width-1; ++i)
    {
        gIndexBuffer_[t++] = (height-2)*width;
        gIndexBuffer_[t++] = i;
        gIndexBuffer_[t++] = i + 1;
        gIndexBuffer_[t++] = (height-2)*width + 1;
        gIndexBuffer_[t++] = (height-3)*width + (i+1);
        gIndexBuffer_[t++] = (height-3)*width + i;
    }
    
    // The index buffer has now been generated. Here's how to use to determine
    // the vertices of a triangle. Suppose you want to determine the vertices
    // of triangle i, with 0 <= i < gNumTriangles. Define:
    //
    // k0 = gIndexBuffer[3*i + 0]
    // k1 = gIndexBuffer[3*i + 1]
    // k2 = gIndexBuffer[3*i + 2]
    //
    // Now, the vertices of triangle i are at positions k0, k1, and k2 (in that
    // order) in the vertex array (which you should allocate yourself at line
    // 27).
    //
    // Note that this assumes 0-based indexing of arrays (as used in C/C++,
    // Java, etc.) If your language uses 1-based indexing, you will have to
    // add 1 to k0, k1, and k2.
}

Vector3f Sphere::calculateNormal(Vector3f p, Matrix4f camera) {
    Vector4f t_position;
    t_position << position_(0), position_(1), position_(2), 1.0f;
    t_position = camera * t_position;
    Vector3f n;
    n << p(0) - t_position(0), p(1) - t_position(1), p(2) - t_position(2);
    n.normalize();
    return n;
}
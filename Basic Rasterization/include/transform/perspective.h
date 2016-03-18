//
//  perspective.h
//  Basic Rasterization
//
//  Created by Tony Zhu on 3/18/16.
//  Copyright © 2016 Tony Zhu. All rights reserved.
//

#ifndef perspective_h
#define perspective_h

#include <Eigen/Dense>

using namespace Eigen;

// Perspective transform
class Perspective {
    
public:
    Perspective();
    Perspective(float l, float r, float b, float t, float n, float f);
    
    float l_;
    float r_;
    float b_;
    float t_;
    float n_;
    float f_;
    Matrix4f ortho_;
    Matrix4f perspective_;
    
    void updateTransformMatrix();
    
};

#endif /* perspective_h */

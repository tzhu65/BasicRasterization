//
//  viewport.h
//  Basic Rasterization
//
//  Created by Tony Zhu on 3/18/16.
//  Copyright © 2016 Tony Zhu. All rights reserved.
//

#ifndef viewport_h
#define viewport_h

#include <Eigen/Dense>

using namespace Eigen;

// Viewport transform
class Viewport {
    
public:
    Viewport();
    Viewport(int width, int height);
    
    int width_;
    int height_;
    Matrix4f viewport_;
    
    void updateTransformMatrix();
    
};

#endif /* viewport_h */

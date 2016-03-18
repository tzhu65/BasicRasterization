//
//  vertex.h
//  Basic Rasterization
//
//  Created by Tony Zhu on 3/18/16.
//  Copyright © 2016 Tony Zhu. All rights reserved.
//

#ifndef vertex_h
#define vertex_h

#include <Eigen/Dense>

using namespace Eigen;

// Vertex of a surface that includes a stored eye space position, color, and normal
class Vertex {
    
public:
    Vertex();
    Vertex(float x, float y, float z);
    
    Vector3f p_;
    Vector3f eye_p_;
    Vector3f color_;
    Vector3f normal_;
    
};

#endif /* vertex_h */

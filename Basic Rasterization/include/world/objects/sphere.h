//
//  sphere.h
//  Basic Rasterization
//
//  Created by Tony Zhu on 3/18/16.
//  Copyright © 2016 Tony Zhu. All rights reserved.
//

#ifndef sphere_h
#define sphere_h

#include <Eigen/Dense>
#include "surface.h"

using namespace Eigen;

// Simple sphere object
class Sphere: public Surface {
    
public:
    Sphere();
    Sphere(float x, float y, float z, float r);
    
    float radius_;
    
    void updateTransformMatrix();
    void createTriangles(int width, int height);
    Vector3f calculateNormal(Vector3f p, Matrix4f camera);
    
};

#endif /* sphere_h */

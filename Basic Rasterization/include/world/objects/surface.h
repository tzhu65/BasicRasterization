//
//  surface.h
//  Basic Rasterization
//
//  Created by Tony Zhu on 3/18/16.
//  Copyright © 2016 Tony Zhu. All rights reserved.
//

#ifndef surface_h
#define surface_h

#include <Eigen/Dense>
#include "material.h"
#include "vertex.h"

using namespace Eigen;

// Surface that contains the triangles, material color, and transformation to world space
class Surface {
    
public:
    Surface();
    
    int gNumVertices_;
    int gNumTriangles_;
    int* gIndexBuffer_;
    Vertex* vertices_;
    Material material_;
    Vector3f position_;
    Matrix4f transform_;
    
    virtual void updateTransformMatrix();
    virtual Vector3f calculateNormal(Vector3f p, Matrix4f camera);
    
};

#endif /* surface_h */

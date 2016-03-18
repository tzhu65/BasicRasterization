//
//  material.h
//  Basic Rasterization
//
//  Created by Tony Zhu on 3/18/16.
//  Copyright © 2016 Tony Zhu. All rights reserved.
//

#ifndef material_h
#define material_h

#include <Eigen/Dense>

using namespace Eigen;

// Color of the material, including ambient, diffusive, and specular colors
class Material {
    
public:
    Material();
    Vector3f ka_;
    Vector3f kd_;
    Vector3f ks_;
    float spower_;
    
};

#endif /* material_h */

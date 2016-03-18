//
//  light.h
//  Basic Rasterization
//
//  Created by Tony Zhu on 3/18/16.
//  Copyright © 2016 Tony Zhu. All rights reserved.
//

#ifndef light_h
#define light_h

#include <Eigen/Dense>

using namespace Eigen;

// Light emitter from infinitely far away
class Light {
    
public:
    Light();
    Light(float x, float y, float z);
    
    Vector3f position_;
    Vector3f tposition_;
    Vector3f color_;
    
};

#endif /* light_h */

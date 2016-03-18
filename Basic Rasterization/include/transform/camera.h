//
//  camera.h
//  Basic Rasterization
//
//  Created by Tony Zhu on 3/18/16.
//  Copyright © 2016 Tony Zhu. All rights reserved.
//

#ifndef camera_h
#define camera_h

#include <Eigen/Dense>

using namespace Eigen;

// Camera transform
class Camera {
    
public:
    Camera();
    Camera(Vector3f u, Vector3f v, Vector3f w, Vector3f e);
    
    Vector3f u_;
    Vector3f v_;
    Vector3f w_;
    Vector3f e_;
    Matrix4f camera_;
    
    void updateTransformMatrix();
    
};

#endif /* camera_h */

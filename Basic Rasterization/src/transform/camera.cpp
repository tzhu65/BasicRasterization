//
//  camera.cpp
//  Basic Rasterization
//
//  Created by Tony Zhu on 3/18/16.
//  Copyright © 2016 Tony Zhu. All rights reserved.
//

#include <Eigen/Dense>
#include "camera.h"

using namespace Eigen;

Camera::Camera() {
    u_ << 1.0f, 0.0f, 0.0f;
    v_ << 0.0f, 1.0f, 0.0f;
    w_ << 0.0f, 0.0f, 1.0f;
    e_ << 0.0f, 0.0f, 0.0f;
    updateTransformMatrix();
}

Camera::Camera(Vector3f u, Vector3f v, Vector3f w, Vector3f e) {
    u_ = u;
    v_ = v;
    w_ = w;
    e_ = e;
    updateTransformMatrix();
}

void Camera::updateTransformMatrix() {
    camera_ << u_(0), v_(0), w_(0), e_(0),
               u_(1), v_(1), w_(1), e_(1),
               u_(2), v_(2), w_(2), e_(2),
                0.0f,  0.0f,  0.0f,  1.0f;
    camera_ = camera_.inverse().eval();
}

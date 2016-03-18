//
//  perspective.cpp
//  Basic Rasterization
//
//  Created by Tony Zhu on 3/18/16.
//  Copyright © 2016 Tony Zhu. All rights reserved.
//

#include <Eigen/Dense>
#include "perspective.h"

Perspective::Perspective() {
    l_ = -0.1f;
    r_ =  0.1f;
    b_ = -0.1f;
    t_ =  0.1f;
    n_ = -0.1f;
    f_ = -1000.0f;
    updateTransformMatrix();
}

Perspective::Perspective(float l, float r, float b, float t, float n, float f) {
    l_ = l;
    r_ = r;
    b_ = b;
    t_ = t;
    n_ = n;
    f_ = f;
    updateTransformMatrix();
}

void Perspective::updateTransformMatrix() {
    ortho_ << 2.0 / (r_ - l_), 0.0, 0.0, -(r_ + l_) / (r_ - l_),
              0.0, 2.0 / (t_ - b_), 0.0, -(t_ + b_) / (t_ - b_),
              0.0, 0.0, 2.0 / (n_ - f_), -(n_ + f_) / (n_ - f_),
              0.0, 0.0, 0.0, 1.0;
    
    perspective_ <<  n_, 0.0, 0.0, 0.0,
                    0.0,  n_, 0.0, 0.0,
                    0.0, 0.0,  n_ + f_, -f_ * n_,
                    0.0, 0.0, 1.0, 0.0;
}

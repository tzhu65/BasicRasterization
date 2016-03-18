//
//  viewport.cpp
//  Basic Rasterization
//
//  Created by Tony Zhu on 3/18/16.
//  Copyright © 2016 Tony Zhu. All rights reserved.
//

#include <Eigen/Dense>
#include "viewport.h"

using namespace Eigen;

Viewport::Viewport() {
    width_ = 512;
    height_ = 512;
    updateTransformMatrix();
}

Viewport::Viewport(int width, int height) {
    width_ = width;
    height_ = height;
    updateTransformMatrix();
}

void Viewport::updateTransformMatrix() {
    viewport_ << width_ / 2.0, 0.0, 0.0, (width_ - 1.0) / 2.0,
                 0.0, height_ / 2.0, 0.0, (height_ - 1.0) / 2.0,
                 0.0, 0.0, 1.0, 0.0,
                 0.0, 0.0, 0.0, 1.0;
}

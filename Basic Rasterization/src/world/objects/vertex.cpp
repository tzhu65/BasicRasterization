//
//  vertex.cpp
//  Basic Rasterization
//
//  Created by Tony Zhu on 3/18/16.
//  Copyright © 2016 Tony Zhu. All rights reserved.
//

#include <Eigen/Dense>
#include "vertex.h"

using namespace Eigen;

Vertex::Vertex() {
    p_ << 0.0f, 0.0f, 0.0f;
    color_ << 0.0f, 0.0f, 0.0f;
}

Vertex::Vertex(float x, float y, float z) {
    p_ << x, y, z;
}

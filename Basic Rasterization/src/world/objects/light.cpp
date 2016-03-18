//
//  light.cpp
//  Basic Rasterization
//
//  Created by Tony Zhu on 3/18/16.
//  Copyright © 2016 Tony Zhu. All rights reserved.
//

#include <Eigen/Dense>
#include "light.h"

Light::Light() {
    position_ << 0.0f, 0.0f, 0.0f;
    color_ << 1.0f, 1.0f, 1.0f;
}

Light::Light(float x, float y, float z) {
    position_ << x, y, z;
    color_ << 1.0f, 1.0f, 1.0f;
}

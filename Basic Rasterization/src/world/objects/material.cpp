//
//  material.cpp
//  Basic Rasterization
//
//  Created by Tony Zhu on 3/18/16.
//  Copyright © 2016 Tony Zhu. All rights reserved.
//

#include <Eigen/Dense>
#include "material.h"

Material::Material() {
    ka_ << 0.0f, 0.0f, 0.0f;
    kd_ << 0.0f, 0.0f, 0.0f;
    ks_ << 0.0f, 0.0f, 0.0f;
    spower_ = 0.0f;
}

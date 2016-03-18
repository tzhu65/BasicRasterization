//
//  transformer.cpp
//  Basic Rasterization
//
//  Created by Tony Zhu on 3/18/16.
//  Copyright © 2016 Tony Zhu. All rights reserved.
//

#include <Eigen/Dense>

#include "transformer.h"
#include "camera.h"
#include "perspective.h"
#include "viewport.h"

using namespace Eigen;

Transformer::Transformer() {
    c_ = Camera();
    p_ = Perspective();
    v_ = Viewport();
}

Transformer::Transformer(Camera c, Perspective p, Viewport v) {
    c_ = c;
    p_ = p;
    v_ = v;
}

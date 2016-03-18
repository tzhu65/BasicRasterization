//
//  surface.cpp
//  Basic Rasterization
//
//  Created by Tony Zhu on 3/18/16.
//  Copyright © 2016 Tony Zhu. All rights reserved.
//

#include <Eigen/Dense>
#include "material.h"
#include "surface.h"

using namespace Eigen;

Surface::Surface() {
    gNumVertices_ = 0;
    gNumTriangles_ = 0;
    gIndexBuffer_ = nullptr;
    vertices_ = nullptr;
    material_ = Material();
}

void Surface::updateTransformMatrix() {
    
}

Vector3f Surface::calculateNormal(Vector3f p, Matrix4f camera) {
    return p;
}

//
//  transformer.h
//  Basic Rasterization
//
//  Created by Tony Zhu on 3/18/16.
//  Copyright © 2016 Tony Zhu. All rights reserved.
//

#ifndef transformer_h
#define transformer_h

#include "camera.h"
#include "perspective.h"
#include "viewport.h"

// Encapsulate all transforms
class Transformer {
    
public:
    Transformer();
    Transformer(Camera c, Perspective p, Viewport v);
    
    Camera c_;
    Perspective p_;
    Viewport v_;
    
};


#endif /* transformer_h */

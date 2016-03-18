//
//  scene.h
//  Basic Rasterization
//
//  Created by Tony Zhu on 3/18/16.
//  Copyright © 2016 Tony Zhu. All rights reserved.
//

#ifndef scene_h
#define scene_h

#include "light.h"
#include "surface.h"

// Scene that holds all the surfaces and lights
class Scene {

public:
    Scene();
    
    Surface** surface_list_;
    Light** light_list_;
    int surface_count_;
    int light_count_;
    float light_intensity_;
    
    void addSurface(Surface* surface);
    void removeAllSurfaces();
    void removeSurface(Surface* surface);
    void addLight(Light* light);
    void removeAllLights();
    void removeLight(Light* light);
    Vector3f calculateColor(Surface& surface, Vector3f& normal, Vector3f& point);
    
};

#endif /* scene_h */

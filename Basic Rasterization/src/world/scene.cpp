//
//  scene.cpp
//  Basic Rasterization
//
//  Created by Tony Zhu on 3/18/16.
//  Copyright © 2016 Tony Zhu. All rights reserved.
//

#include "light.h"
#include "scene.h"
#include "surface.h"

Scene::Scene() {
    surface_list_ = new Surface*[0];
    surface_count_ = 0;
    
    light_list_ = new Light*[0];
    light_count_ = 0;
}

void Scene::addSurface(Surface* surface) {
    surface_count_++;
    Surface** surface_list = new Surface*[surface_count_];
    
    // Copy over the previous surfaces
    for (int i = 0; i < surface_count_ - 1; i++) {
        surface_list[i] = surface_list_[i];
    }
    delete surface_list_;
    surface_list[surface_count_ - 1] = surface;
    surface_list_ = surface_list;
}

void Scene::addLight(Light* light) {
    light_count_++;
    Light** light_list = new Light*[light_count_];
    
    // Copy over the previous lights
    for (int i = 0; i < light_count_ - 1; i++) {
        light_list[i] = light_list_[i];
    }
    delete light_list_;
    light_list[light_count_ - 1] = light;
    light_list_ = light_list;
}

void Scene::removeAllSurfaces() {
    surface_list_ = new Surface*[0];
    surface_count_ = 0;
}

void Scene::removeSurface(Surface* surface) {
    surface_count_--;
}

void Scene::removeAllLights() {
    light_list_ = new Light*[0];
    light_count_ = 0;
}

void Scene::removeLight(Light* light) {
    light_count_--;
}

Vector3f Scene::calculateColor(Surface& surface, Vector3f& normal, Vector3f& point) {
    Vector3f color(0.0f, 0.0f, 0.0f);
    
    // Ambient
    Vector3f ambient;
    ambient = surface.material_.ka_ * light_intensity_;
    color += ambient;
    
    for (int i = 0; i < light_count_; i++) {
        Light* light = light_list_[i];
        Vector3f lightp = light->tposition_;
        Vector3f lightc = light->color_;
        
        // Diffusive
        Vector3f l = lightp - point;
        l.normalize();
        float dp = normal.dot(l);
        dp = dp > 0 ? dp : 0;
        Vector3f diffusive(surface.material_.kd_ * dp);
        
        // Specular
        Vector3f v = -point;
        v.normalize();
        Vector3f h = (v + l);
        h.normalize();
        float dp2 = normal.dot(h);
        dp2 = dp2 > 0 ? dp2 : 0;
        Vector3f specular(surface.material_.ks_ * pow(dp2, surface.material_.spower_));
        
        color += diffusive + specular;
    }
    
    return color;
}

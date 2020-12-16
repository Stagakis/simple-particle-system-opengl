//
// Created by stagakis on 15/12/20.
//

#include "OrbitEmitter.h"
#include <iostream>
OrbitEmitter::OrbitEmitter(Drawable *_model, int number, float _radius_min, float _radius_max) : IntParticleEmitter(_model, number), radius_min(_radius_min), radius_max(_radius_max){
    particle_radius.resize(number_of_particles, 0.0f);
    for(int i = 0; i < number_of_particles; i++){
        createNewParticle(i);
    }
}

void OrbitEmitter::updateParticles(float time, float dt, glm::vec3 camera_pos) {
    //Make the particles move in a circle around "radius" of the center of the emitter
}

void OrbitEmitter::createNewParticle(int index) {
    //InitializeParticles
}

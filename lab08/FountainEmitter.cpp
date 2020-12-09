//
// Created by stagakis on 9/12/20.
//

#include "FountainEmitter.h"
#include <iostream>
#include <algorithm>


FountainEmitter::FountainEmitter(Drawable *_model, int number) : ParticleEmitterInt(_model, number) {

}

void FountainEmitter::updateParticles(float time, float dt) {

    if(active_particles < number_of_particles) {
        int batch = 25;
        int limit = std::min(number_of_particles - active_particles, batch);
        for(int i = 0 ; i < limit; i++){
            createNewParticle(active_particles);
            active_particles++;
        }
    }

    for(int i = 0; i < active_particles; i++){
        particleAttributes & particle = p_attributes[i];
        if(particle.position.y < emitter_pos.y - 10.0f){
            createNewParticle(i);
        }
        particle.angle += 90*dt;
        particle.position = particle.position + particle.velocity*dt + particle.accel*(dt*dt)*0.5f;
        particle.velocity = particle.velocity + particle.accel*dt;
    }
}

void FountainEmitter::createNewParticle(int index){
    particleAttributes & particle = p_attributes[index];

    particle.position = emitter_pos + glm::vec3(1 - RAND*2, RAND, 1 - RAND*2);
    particle.velocity = glm::vec3( 3 - RAND*6,10,3 - RAND*6)*4.0f;
    particle.mass = RAND + 0.5f;
    particle.rot_axis = glm::normalize(glm::vec3(1 - 2*RAND, 1 - 2*RAND, 1 - 2*RAND));
    particle.accel = glm::vec3(0.0f, -9.8f, 0.0f); //gravity force
    particle.angle = RAND*360;
    particle.life = 1.0f; //mark it alive
}

//
// Created by stagakis on 9/12/20.
//

#include "FountainEmitter.h"

FountainEmitter::FountainEmitter(Drawable *_model, int number) : ParticleEmitterInt(_model, number) {

}

void FountainEmitter::updateParticles(float time) {
    for(int i; i < number_of_particles; i++){
        particleAttributes & particle = p_attributes[i];

        if(particle.position.y < emitter_pos.y){
            createNewParticle(i);
        }

        //particle.position = particle.position + particle.velocity*dt + 0.5*particle.accel*(dt*dt);
        //particle.velocity = particle.velocity + particle.accel*dt;
    }
}

void FountainEmitter::initializeParticles() {
    for(int i; i < number_of_particles; i++){
        particleAttributes & particle = p_attributes[i];

        particle.position = emitter_pos;
        particle.velocity = glm::vec3(2-rand()%4,5,2-rand()%4);
        particle.mass = rand()%2 + 0.5;
        particle.accel = glm::vec3(0.0f, -particle.mass*9.8, 0.0f); //gravity

    }
}

void FountainEmitter::createNewParticle(int index){

}

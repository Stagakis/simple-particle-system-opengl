//
// Created by stagakis on 9/12/20.
//

#include "FountainEmitter.h"
#include "iostream"
FountainEmitter::FountainEmitter(Drawable *_model, int number) : ParticleEmitterInt(_model, number) {

    //initializeParticles();

}

void FountainEmitter::updateParticles(float time, float dt) {

    if(active_particles < number_of_particles) {
        for(int i = 0 ; i < 5; i++){
            createNewParticle(active_particles);
            active_particles++;
        }
    }

    for(int i = 0; i < active_particles; i++){

        particleAttributes & particle = p_attributes[i];

        if(particle.position.y < emitter_pos.y - 1.0f){
            createNewParticle(i);
        }

        particle.position = particle.position + particle.velocity*dt + particle.accel*(dt*dt)*0.5f;
        particle.velocity = particle.velocity + particle.accel*dt;

        //std::cout << particle.accel.y << std::endl;

        auto t = glm::translate(glm::mat4(1.0f), particle.position);
        auto r = glm::mat4(1.0f);
        auto s = glm::scale(glm::mat4(1.0f), glm::vec3(particle.mass));
        transformations[i] = t * r * s;
    }
}

void FountainEmitter::initializeParticles() {
    for(int i=0; i < number_of_particles/3; i++){
        createNewParticle(i);
    }
    active_particles = number_of_particles/3;
}

void FountainEmitter::createNewParticle(int index){
    particleAttributes & particle = p_attributes[index];

    particle.position = emitter_pos + glm::vec3(1 - RAND*2, RAND, 1 - RAND*2);
    particle.velocity = glm::vec3( 4 - RAND*8,10,4 - RAND*8)*2.0f;
    particle.mass = RAND + 0.1f;
    particle.accel = glm::vec3(0.0f, -9.8, 0.0f); //gravity
    particle.life = 1.0f;
}

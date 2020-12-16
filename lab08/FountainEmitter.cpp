#include "FountainEmitter.h"
#include <iostream>
#include <algorithm>

FountainEmitter::FountainEmitter(Drawable *_model, int number) : IntParticleEmitter(_model, number) {}

void FountainEmitter::updateParticles(float time, float dt, glm::vec3 camera_pos) {

    //This is for the fountain to slowly increase the number of its particles to the max amount
    //instead of shooting all the particles at once
    if (active_particles < number_of_particles) {
        int batch = 14;
        int limit = std::min(number_of_particles - active_particles, batch);
        for (int i = 0; i < limit; i++) {
            createNewParticle(active_particles);
            active_particles++;
        }
    }
    else {
        active_particles = number_of_particles; //In case we resized our ermitter to a smaller particle number
    }

    for(int i = 0; i < active_particles; i++){
        particleAttributes & particle = p_attributes[i];

        if(particle.position.y < emitter_pos.y - 10.0f || particle.life == 0.0f){
            createNewParticle(i);
        }

        particle.rot_angle += 90*dt; 

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
    particle.rot_angle = RAND*360;
    particle.life = 1.0f; //mark it alive
}

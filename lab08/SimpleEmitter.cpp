//
// Created by stagakis on 9/12/20.
//

#include "SimpleEmitter.h"
#include "iostream"
void SimpleEmitter::updateParticles(float time, float dt) {

    for (int i = 0; i < number_of_particles; i++) {
        p_attributes[i].position = glm::vec3(rand() % 10, rand() % 10, rand() % 10);
        p_attributes[i].rot_axis =  glm::vec3(rand() % 10, rand() % 10, rand() % 10);
        p_attributes[i].angle = rand()%360;

        auto t = glm::translate(glm::mat4(), p_attributes[i].position);
        auto r = glm::rotate(glm::mat4(), glm::radians(p_attributes[i].angle), p_attributes[i].rot_axis);

        transformations[i] = t * r;
    }
}

SimpleEmitter::SimpleEmitter(Drawable *_model, int number) : ParticleEmitterInt(_model, number) {}

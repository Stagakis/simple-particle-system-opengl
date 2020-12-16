#include "ParticleEmitterInt.h"
#include "iostream"
#include <algorithm>
#include <execution>

ParticleEmitterInt::ParticleEmitterInt(Drawable* _model, int number) {
    model = _model;
    number_of_particles = number;
    emitter_pos = glm::vec3(0.0f, 0.0f, 0.0f);
    p_attributes.resize(number_of_particles, particleAttributes());
    transformations.resize(number_of_particles, glm::mat4(0.0f));

    configureVAO();
}

void ParticleEmitterInt::renderParticles(int time) {
    if(time<1) {
        bindAndUpdateBuffers();
    }
    glDrawElementsInstanced(GL_TRIANGLES, 3 * model->indices.size(), GL_UNSIGNED_INT, 0, number_of_particles);
}

void ParticleEmitterInt::configureVAO()
{
    glGenVertexArrays(1, &emitterVAO);
    glBindVertexArray(emitterVAO);


    //We are using the model's buffer but since they are already in the GPU from the Drawable's constructor we just need to configure 
    //our own VAO by using glVertexAttribPointer and glEnableVertexAttribArray but without sending any data with glBufferData.
    glBindBuffer(GL_ARRAY_BUFFER, model->verticesVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    if (model->indexedNormals.size() != 0) {
        glBindBuffer(GL_ARRAY_BUFFER, model->normalsVBO);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(1);
    }


    if (model->indexedUVS.size() != 0) {
        glBindBuffer(GL_ARRAY_BUFFER, model->uvsVBO);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(2);
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->elementVBO);

    //GLSL treats mat4 data as 4 vec4. So we need to enable attributes 3,4,5 and 6, one for each vec4
    glGenBuffers(1, &transformations_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, transformations_buffer);
    std::size_t vec4Size = sizeof(glm::vec4);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(1 * vec4Size));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));

    //This tells opengl how each particle should get data its slice of data from the mat4
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);


    glBindVertexArray(0);
}

void ParticleEmitterInt::bindAndUpdateBuffers()
{
    //Calculate the model matrix in parallel to save performance
    std::transform(std::execution::par_unseq, p_attributes.begin(), p_attributes.end(), transformations.begin(),
        [](particleAttributes p)->glm::mat4 {
            if (p.life == 0) return glm::mat4(0.0f);
            auto r = glm::rotate(glm::mat4(), glm::radians(p.rot_angle), p.rot_axis);
            auto s = glm::scale(glm::mat4(), glm::vec3(p.mass, p.mass, p.mass));
            auto t = glm::translate(glm::mat4(), p.position);
            return t * r * s;
        });

    //Bind the coresponding VAO of the model, since we are going to draw it
    glBindVertexArray(emitterVAO);

    //Send transformation data to the GPU
    glBindBuffer(GL_ARRAY_BUFFER, transformations_buffer);
    glBufferData(GL_ARRAY_BUFFER, number_of_particles * sizeof(glm::mat4), NULL, GL_STREAM_DRAW); // Buffer orphaning and reallocating to avoid synchronization, see https://www.khronos.org/opengl/wiki/Buffer_Object_Streaming
    glBufferSubData(GL_ARRAY_BUFFER, 0, number_of_particles * sizeof(glm::mat4), &transformations[0]); //Sending data

    //GLSL treats mat4 data as 4 vec4. So we need to enable attributes 3,4,5 and 6, one for each vec4

}

void ParticleEmitterInt::changeParticleNumber(int new_number) {
    if(new_number == number_of_particles) return;

    number_of_particles = new_number;
    p_attributes.resize(number_of_particles, particleAttributes());
    transformations.resize(number_of_particles, glm::mat4(0.0f));
}

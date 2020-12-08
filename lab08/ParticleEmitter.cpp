#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter(Drawable* _model, int number) {
    model = _model;
    number_of_particles = number;

    transformations.resize(number_of_particles, glm::mat4(1.0f));

    for(int i = 0 ; i< number_of_particles; i++){
        glm::mat4 tranlsation = glm::translate(glm::mat4(), glm::vec3(rand() % 10, rand() % 10, rand() % 10));
        transformations[i] = tranlsation;
    }
    sendDataToGPU();
}

void ParticleEmitter::renderParticles() {
    glBindVertexArray(model->VAO);
    glDrawElementsInstanced(GL_TRIANGLES, 3*model->indices.size(), GL_UNSIGNED_INT, 0, number_of_particles);
}

void ParticleEmitter::updateParticles(float time)
{
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glInvalidateBufferData(GL_ARRAY_BUFFER); //make orhpan

    for (int i = 0; i < number_of_particles; i++) {
        glm::mat4 tranlsation = glm::translate(glm::mat4(), glm::vec3(rand() % 10, rand() % 10, rand() % 10));
        transformations[i] = tranlsation;
    }
    sendDataToGPU();
}

void ParticleEmitter::sendDataToGPU()
{
    glBindVertexArray(model->VAO);


    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, number_of_particles * sizeof(glm::mat4), &transformations[0], GL_STREAM_DRAW);

    std::size_t vec4Size = sizeof(glm::vec4);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(1 * vec4Size));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));

    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

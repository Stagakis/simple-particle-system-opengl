#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter(Drawable* _model, int number) {
    model = _model;
    for(int i = 0 ; i< number ; i++){
        transformations.push_back((glm::mat4(1.0f)));
        glBindVertexArray(model->VAO);
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

    }
    number_of_particles = number;
}

void ParticleEmitter::renderParticles() {
    glBindVertexArray(model->VAO);
    glDrawElementsInstanced(GL_TRIANGLES, 3*model->indexedVertices.size(), GL_UNSIGNED_INT, 0, number_of_particles);
}

#pragma once
#include <GL/glew.h>
#include <Particle.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "model.h"

class ParticleEmitter
{
public:
    int number_of_particles;
    std::vector<Particle> particle_list;
    std::vector<glm::mat4> transformations;
    GLuint modelIndecesVBO, modelTexturesVBO, modelNormalsVBO;
	GLuint particleTransforms;
    unsigned int buffer;

	ParticleEmitter(Drawable* _model, int number);
	void renderParticles();
	void updateParticles(float time);

private:
    void bindAndUpdateBuffers();
    Drawable* model;
};


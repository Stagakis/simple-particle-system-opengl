#pragma once
#include <GL/glew.h>
#include <Particle.h>
#include <vector>
#include <glm/glm.hpp>
#include "model.h"
class ParticleEmitter
{
public:
    int number_of_particles;
    std::vector<Particle> particle_list;
    std::vector<glm::mat4> transformations;
    GLuint modelIndecesVBO, modelTexturesVBO, modelNormalsVBO;
	GLuint particleTransforms;

	ParticleEmitter(Drawable* _model, int number);
	void renderParticles();
	void updateParticles();
private:
    Drawable* model;

};


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

    std::vector<glm::mat4> transformations;

    GLuint modelIndecesVBO, modelTexturesVBO, modelNormalsVBO;
	GLuint particleTransforms;

	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> rot_axis;
	std::vector<float> angles;

	std::vector<glm::vec3> accels;
	std::vector<glm::vec3> velocities;

	std::vector<float> life_times;

    unsigned int transformations_buffer;

	ParticleEmitter(Drawable* _model, int number);
	void renderParticles();
	void updateParticles(float time);

private:
    void bindAndUpdateBuffers();
    Drawable* model;
    Particle particle_blueprint;
};


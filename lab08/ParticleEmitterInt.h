#pragma once
#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "model.h"

struct particleAttributes{
    glm::vec3 position = glm::vec3(0,0,0);
    glm::vec3 rot_axis= glm::vec3(0,1,0);
    float angle = 0.0f;
    glm::vec3 accel = glm::vec3(0,0,0);
    glm::vec3 velocity= glm::vec3(0,0,0);
    float life = 0.0f;
    float mass = 0.0f;
};

class ParticleEmitterInt
{
public:
    int number_of_particles;
    std::vector<glm::mat4> transformations;
	std::vector<particleAttributes> p_attributes;
    glm::vec3 emitter_pos;

	ParticleEmitterInt(Drawable* _model, int number);
	void renderParticles();
	virtual void updateParticles(float time) = 0;

private:
    void bindAndUpdateBuffers();
    GLuint transformations_buffer;
    Drawable* model;
};


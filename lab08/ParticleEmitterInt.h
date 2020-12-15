#pragma once
#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "model.h"

//Gives a random number between 0 and 1
#define RAND ((float) rand()) / (float) RAND_MAX

struct particleAttributes{
    glm::vec3 position = glm::vec3(0,0,0);
    glm::vec3 rot_axis= glm::vec3(0,1,0);
    float rot_angle = 0.0f;
    glm::vec3 accel = glm::vec3(0,0,0);
    glm::vec3 velocity = glm::vec3(0,0,0);
    float life = 0.0f;
    float mass = 0.0f;

    float dist_from_camera = 0.0f;
    bool operator < (const particleAttributes & p) const
    {
        return dist_from_camera <= p.dist_from_camera;
    }

};


//ParticleEmitterInt is an interface class. Emitter classes must derive from this one and implement the updateParticles method
class ParticleEmitterInt
{
public:
    int number_of_particles;
    std::vector<glm::mat4> transformations;
	std::vector<particleAttributes> p_attributes;

    glm::vec3 emitter_pos; //the origin of the emitter

	ParticleEmitterInt(Drawable* _model, int number);
	void renderParticles(int time = 0);
	virtual void updateParticles(float time, float dt) = 0;

    Drawable* model;

private:
    void bindAndUpdateBuffers();
    GLuint transformations_buffer;
};


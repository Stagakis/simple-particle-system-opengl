#pragma once
#include<glm/glm.hpp>

class Particle
{
	Particle();
	glm::vec3 position;
	glm::vec3 accel;
	glm::vec3 velocity;
	float life_time;
	float mass;
};


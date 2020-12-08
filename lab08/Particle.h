#pragma once
#include<glm/glm.hpp>

class Particle
{
	Particle();
	void bind();

	/*// Maybe not needed
	glm::vec3 position;
	glm::vec3 rot_axis;
	float angle;

	glm::vec3 accel;
	glm::vec3 velocity;
	
	float life_time;
	float mass;
	//*/

private:
	Drawable* model;
	GLuint modelIndecesVBO, modelTexturesVBO, modelNormalsVBO;
	GLuint texture;
};


#pragma once
#include<glm/glm.hpp>
#include<model.h>
class Particle
{
public:
	Particle();
	void bind();

private:
	Drawable* model;
	GLuint modelIndecesVBO, modelTexturesVBO, modelNormalsVBO;
	GLuint texture;
};


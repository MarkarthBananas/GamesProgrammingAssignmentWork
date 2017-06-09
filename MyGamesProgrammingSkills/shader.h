#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>
#include "motion.h"
#include "camera.h"

class shader
{
public:
	//initialises shaders from filename (.vs and .fs files)
	shader(const std::string& fileName);

	//bind function for shaders
	void Bind();

	//updates shaders
	void Update(const motion& pMotion, const camera& pCamera);

	//destructor for shaders
	virtual ~shader();

protected:
private:
	//states number of shaders
	static const unsigned int NUM_SHADERS = 2;
	
	//constructor for shaders
	shader(const shader& other) {}
	void operator=(const shader& other) {}

	//holds motion class information and uniforms
	enum
	{
		MOTION_U,

		NUM_UNIFORMS
	};

	//open gl initialisation for num shaders, uniforms and the program
	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];
};

#endif

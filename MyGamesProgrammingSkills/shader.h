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
	shader(const std::string& fileName);

	void Bind();
	void Update(const motion& pMotion, const camera& pCamera);

	virtual ~shader();

protected:
private:
	static const unsigned int NUM_SHADERS = 2;
	shader(const shader& other) {}
	void operator=(const shader& other) {}

	enum
	{
		MOTION_U,

		NUM_UNIFORMS
	};

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];
};

#endif //SHADER_H

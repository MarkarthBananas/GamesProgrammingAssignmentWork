#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL/glew.h>

class texture
{
public:
	texture(const std::string& fileName);

	void Bind(unsigned int unit);

	virtual ~texture();

protected:

private:
	texture(const texture& other);
	texture& operator=(const texture& other);

	GLuint m_texture;
};

#endif //TEXTURE_H
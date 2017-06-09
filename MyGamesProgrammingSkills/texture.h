#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL/glew.h>

class texture
{
public:
	
	//texture function taking in file name (marbletexture.jpg) for the texture i have used on my model
	texture(const std::string& fileName);

	//function for binding texture
	void Bind(unsigned int unit);

	//destructor for texture
	virtual ~texture();

protected:

private:
	//constructor
	texture(const texture& other);
	texture& operator=(const texture& other);

	//open gl initialisation for texture
	GLuint m_texture;
};

#endif
#include "texture.h"
#include "stb_image.h"
#include <assert.h>
#include <iostream>
#include <assert.h>

//initialise texture from filename (marbletexture.jpg file)
texture::texture(const std::string& fileName)
{
	int width, height, numComponents;
	unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);

	//error handling for if texture fails to load
	if (imageData == NULL)
	{
		std::cerr << "Texture loading failed for texture: " << fileName << std::endl;
	}

	//generates and binds texture
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//renders texture image
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	stbi_image_free(imageData);
}

//destructor for texture
texture::~texture()
{
	glDeleteTextures(1, &m_texture);
}

//binds texture
void texture::Bind(unsigned int unit)
{
	assert(unit >= 0 && unit <= 31); //assert test to ensure unit is >= 0 and <= 31

	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}
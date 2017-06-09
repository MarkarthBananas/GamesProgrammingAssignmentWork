#pragma once
#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include "obj_loader.h"

class vertex
{
public:
	//initialises vertex with position, texCoord and normal values
	vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3 normal = glm::vec3(0, 0, 0))
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
	}

	//gets the values of position, texCoord and normal
	inline glm::vec3* GetPos() { return &pos; }
	inline glm::vec2* GetTexCoord() { return &texCoord; }
	inline glm::vec3* GetNormal() { return &normal; }


protected:

private:
	//variables for positon, texCoord and normal
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;

};

class mesh
{
public:
	//initialises mesh with indices and vertices, along with the files for the mesh .vs and .fs
	mesh(vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	mesh(const std::string& fileName);

	//draw function for mesh
	void Draw();

	//destructor for mesh
	virtual ~mesh();

protected:

private:

	//constructor for the mesh
	mesh(const mesh& other);
	void operator=(const mesh& other);

	//initialises the mesh
	void InitMesh(const IndexedModel& model);

	//holds position, texCoord, normal, index and buffers
	enum
	{
		POSITION_VB,
		TEXCOORD_VB,
		NORMAL_VB,

		INDEX_VB,

		NUM_BUFFERS

	};

	//initialises open gl object and buffers for mesh
	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];

	//counts the draw amount
	unsigned int m_drawCount;
};

#endif MESH_H

#pragma once
#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include "obj_loader.h"

class vertex
{
public:
	vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3 normal = glm::vec3(0, 0, 0))
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
	}

	inline glm::vec3* GetPos() { return &pos; }
	inline glm::vec2* GetTexCoord() { return &texCoord; }
	inline glm::vec3* GetNormal() { return &normal; }


protected:

private:
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;

};

class mesh
{
public:
	mesh(vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	mesh(const std::string& fileName);

	void Draw();

	virtual ~mesh();

protected:

private:
	mesh(const mesh& other);
	void operator=(const mesh& other);

	void InitMesh(const IndexedModel& model);

	enum
	{
		POSITION_VB,
		TEXCOORD_VB,
		NORMAL_VB,

		INDEX_VB,

		NUM_BUFFERS

	};

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;
};

#endif MESH_H

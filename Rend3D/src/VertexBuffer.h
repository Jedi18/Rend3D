#pragma once

	#include <glad/glad.h>

class VertexBuffer
{
private:
	unsigned int id;
public:
	VertexBuffer(unsigned int size,const void* data);
	~VertexBuffer();
	void Bind() const;
	void Unbind() const;
};
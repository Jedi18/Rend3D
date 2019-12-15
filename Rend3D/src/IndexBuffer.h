#pragma once

#include <glad/glad.h>

class IndexBuffer
{
private:
	unsigned int id;
public:
	IndexBuffer(unsigned int size, const void* data);
	~IndexBuffer();
	void Bind() const;
	void Unbind() const;
};
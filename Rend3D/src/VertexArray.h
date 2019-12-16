#pragma once

#include<glad/glad.h>
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
private:
	unsigned int id;
public:
	VertexArray();
	~VertexArray();
	void AttributeLayout(VertexBuffer& vbo, VertexBufferLayout& layout);
	void Bind() const;
	void Unbind() const;
};
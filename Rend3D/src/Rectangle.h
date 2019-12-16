#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"

class Rectangle
{
private:
	float vertices[12];
	unsigned int indices[6];
public:
	VertexBuffer vbo;
	IndexBuffer ibo;
	VertexBufferLayout layout;
	Rectangle(VertexArray& vao);
	void Draw() const;
};
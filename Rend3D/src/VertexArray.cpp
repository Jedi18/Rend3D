#include "VertexArray.h"
#include<iostream>

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &id);
	Bind();
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &id);
}

void VertexArray::AttributeLayout(VertexBuffer& vbo, VertexBufferLayout& layout)
{
	vbo.Bind();
	unsigned int count = 0;

	for (VertexBufferLayout::BufferElement element : layout.GetLayout())
	{
		glEnableVertexAttribArray(count);
		glVertexAttribPointer(count, element.count, element.type, element.normalized, layout.GetStride(), 0);
		count++;
	}
}

void VertexArray::Bind() const
{
	glBindVertexArray(id);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

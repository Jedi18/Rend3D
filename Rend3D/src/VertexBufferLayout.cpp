#include "VertexBufferLayout.h"

VertexBufferLayout::VertexBufferLayout()
	:
	stride(0),
	elements()
{
}

const std::vector<VertexBufferLayout::BufferElement> VertexBufferLayout::GetLayout()
{
	return elements;
}

int VertexBufferLayout::GetStride() const
{
	return stride;
}

#pragma once

#include<vector>
#include<glad/glad.h>

class VertexBufferLayout
{
public:
	struct BufferElement
	{
		GLint count;
		GLenum type;
		GLboolean normalized;
	};
private:
	std::vector<BufferElement> elements;
	int stride;
public:
	VertexBufferLayout();
	const std::vector<BufferElement> GetLayout();
	int GetStride() const;

	template<typename T>
	void Push(int count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(int count)
	{
		elements.push_back({ count, GL_FLOAT, GL_FALSE });
		stride += count * sizeof(float);
	}

	template<>
	void Push<unsigned int>(int count)
	{
		elements.push_back({ count, GL_UNSIGNED_INT, GL_FALSE });
		stride += count * sizeof(unsigned int);
	}

	template<>
	void Push<unsigned char>(int count)
	{
		elements.push_back({ count, GL_UNSIGNED_BYTE, GL_TRUE });
		stride += count * sizeof(unsigned char);
	}
};

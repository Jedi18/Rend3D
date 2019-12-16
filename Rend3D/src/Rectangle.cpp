#include "Rectangle.h"

Rectangle::Rectangle(VertexArray& vaoin)
	:
	vertices{
		0.5f, 0.5f, 1.0f,
		-0.5f, 0.5f, 1.0f,
		-0.5f, -0.5f, 1.0f,
		0.5f, -0.5f, 1.0f
		},
	indices{
		0, 1, 2,
		2, 3, 0
		},
	vbo(sizeof(vertices), vertices),
	ibo(sizeof(indices), indices),
	layout()
{
	layout.Push<float>(3);
	vaoin.AttributeLayout(vbo, layout);
}

void Rectangle::Draw() const
{
	// assumes that corresponding vao is bound before calling this function
	ibo.Bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

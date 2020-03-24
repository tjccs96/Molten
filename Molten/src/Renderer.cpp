#include "Renderer.h"
#include <iostream>


void glClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

void Renderer::clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.bind();
	va.bind();
	ib.bind();
	glCall(glDrawElements(GL_TRIANGLES, ib.get_count(), GL_UNSIGNED_INT, nullptr));
}

#include "VertexBuffer.h"
#include "Renderer.h"


VertexBuffer::VertexBuffer(const void* data, const unsigned int size)
{
	glGenBuffers(1, &m_renderer_id_);
	glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id_);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW); // or 4 * 2
}

VertexBuffer::~VertexBuffer() 
{
	glCall(glDeleteBuffers(1, &m_renderer_id_));
}

void VertexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id_);
}

void VertexBuffer::unbind()	const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

#include "Renderer.h"


IndexBuffer::IndexBuffer(const unsigned int* data, const unsigned int count)
	: m_count_{ count }
{
	ASSERT(sizeof(unsigned int) == sizeof(GLuint));

	glGenBuffers(1, &m_renderer_id_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW); // or 4 * 2
}

IndexBuffer::~IndexBuffer()
{
	glCall(glDeleteBuffers(1, &m_renderer_id_));
}

void IndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id_);
}

void IndexBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

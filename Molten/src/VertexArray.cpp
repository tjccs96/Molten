#include "Renderer.h"

VertexArray::VertexArray()
{
	glCall(glGenVertexArrays(1, &m_renderer_id_));
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_renderer_id_);
}

void VertexArray::add_buffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	bind();
	vb.bind();
	const auto& elements = layout.get_elements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.get_stride(), reinterpret_cast<const void*>(offset));
		offset += element.count * VertexBufferElement::get_size_of_type(element.type);
	}
}

void VertexArray::bind() const
{
	glBindVertexArray(m_renderer_id_);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}

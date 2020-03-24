#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
private:
	unsigned int m_renderer_id_;
public:
	VertexArray();
	~VertexArray();

	void add_buffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void bind() const;
	void unbind() const;
};
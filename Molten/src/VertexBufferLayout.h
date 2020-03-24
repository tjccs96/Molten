#pragma once

#include <vector>
#include <GL/glew.h>
#include "Renderer.h"
#include "Logging.h"

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int get_size_of_type(const unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:
			return 4;
		case GL_UNSIGNED_INT:
			return 4;
		case GL_UNSIGNED_BYTE:
			return 1;
		}
		ASSERT(false);
		return 0;
	}
};


class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_elements_;
	unsigned int m_stride_;
public:
	VertexBufferLayout()
		: m_stride_{0} {}

	template<typename T>
	void push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void push<float>(const unsigned int count)
	{
		m_elements_.push_back({ GL_FLOAT, count, GL_FALSE });
		m_stride_ += count * VertexBufferElement::get_size_of_type(GL_FLOAT);
	}

	template<>
	void push<unsigned int>(const unsigned int count)
	{
		m_elements_.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_stride_ += count * VertexBufferElement::get_size_of_type(GL_UNSIGNED_INT);
	}

	template<>
	void push<unsigned char>(const unsigned int count)
	{
		m_elements_.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_stride_ += count * VertexBufferElement::get_size_of_type(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<VertexBufferElement>& get_elements() const { return m_elements_; }
	inline unsigned int get_stride() const { return m_stride_; }
};

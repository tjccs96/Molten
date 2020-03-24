#pragma once

class IndexBuffer
{
private:
	unsigned int m_renderer_id_;
	unsigned int m_count_;
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void bind() const;
	void unbind() const;

	inline unsigned int get_count() const { return m_count_; }
};

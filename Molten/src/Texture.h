#pragma once

#include "Renderer.h"

class Texture
{
	unsigned int m_renderer_id_;
	std::string m_filepath_;
	unsigned char* m_local_buffer_;
	int m_width_, m_height_, m_bpp_;

public:
	Texture(const std::string& file_path);
	~Texture();

	void bind(unsigned int slot = 0) const;
	void unbind() const;

	inline int get_width() const { return m_width_; }
	inline int get_height() const { return m_height_; }
};
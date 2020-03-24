#include "Texture.h"
#include "stb_image/stb_image.h"


Texture::Texture(const std::string& file_path)
	: m_renderer_id_{ 0 }, m_filepath_{ file_path }, m_local_buffer_{ nullptr }, m_width_{ 0 }, m_height_{ 0 }, m_bpp_{ 0 }
{
	// Note to self: always prefer initialization lists like the above.
	stbi_set_flip_vertically_on_load(1);
	m_local_buffer_ = stbi_load(file_path.c_str(), &m_width_, &m_height_, &m_bpp_, 4);
	
	glCall(glGenTextures(1, &m_renderer_id_)); // Bind one texture to renderID
	glCall(glBindTexture(GL_TEXTURE_2D, m_renderer_id_));
	// This 4 parameters need to always be specified
	glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width_, m_height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_local_buffer_);
	glCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (m_local_buffer_)
		stbi_image_free(m_local_buffer_);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_renderer_id_);
}

void Texture::bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_renderer_id_);
}

void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

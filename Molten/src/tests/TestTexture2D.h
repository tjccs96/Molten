#pragma once

#include "Test.h"
#include "Texture.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#include <memory>

namespace test {
	
	class TestTexture2D : public Test
	{
	public:
		TestTexture2D();
		~TestTexture2D() = default;

		void on_update(float delta_time) override;
		void on_render() override;
		void on_imgui_render() override;
	private:
		std::unique_ptr<VertexArray> m_vao_;
		std::unique_ptr<IndexBuffer> m_index_buffer_;
		std::unique_ptr<Shader> m_shader_;
		std::unique_ptr<Texture> m_texture_;
		std::unique_ptr<VertexBuffer> m_vertex_buffer_;

		glm::mat4 m_proj_;
		glm::mat4 m_view_;
		glm::vec3 m_translation_a_;
		glm::vec3 m_translation_b_;
	};
}
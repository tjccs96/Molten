#include "TestTexture2D.h"
#include "Renderer.h"
#include "imgui/imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test {
	
	TestTexture2D::TestTexture2D()
		: m_proj_(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)), 
		m_view_(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))), 
		m_translation_a_(200, 200, 0), m_translation_b_(400, 200, 0)
		
	{
		float vertices[] = {
			-50.0f, -50.0f, 0.0f, 0.0f,
		 	 50.0f, -50.0f, 1.0f, 0.0f,
			 50.0f,  50.0f, 1.0f, 1.0f,
			-50.0f,  50.0f, 0.0f, 1.0f
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		glCall(glEnable(GL_BLEND));
		glCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		
		m_vao_ = std::make_unique<VertexArray>();
		m_vertex_buffer_ = std::make_unique<VertexBuffer>(vertices, 4 * 4 * sizeof(float));
		VertexBufferLayout layout;
		layout.push<float>(2);
		layout.push<float>(2);
		std::vector<int> a = {1,2,3};
		
		m_vao_->add_buffer(*m_vertex_buffer_, layout);
		m_index_buffer_ = std::make_unique<IndexBuffer>(indices, 6);

		m_shader_ = std::make_unique<Shader>("res/shaders/Basic.shader");
		m_shader_->bind();
		m_shader_->set_uniform4_f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

		m_texture_ = std::make_unique<Texture>("res/textures/cpp.png");
		m_shader_->set_uniform1_i("u_Texture", 0);
	}

	void TestTexture2D::on_update(float delta_time)
	{
	}

	void TestTexture2D::on_render()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		Renderer renderer;

		m_texture_->bind();

		{
			glm::mat4 model_matrix = glm::translate(glm::mat4(1.0f), m_translation_a_);
			glm::mat4 model_view_projection = m_proj_ * m_view_ * model_matrix;
			m_shader_->bind();
			m_shader_->set_uniform_mat4_f("u_MVP", model_view_projection);
			renderer.draw(*m_vao_, *m_index_buffer_, *m_shader_);
		}

		{
			glm::mat4 model_matrix = glm::translate(glm::mat4(1.0f), m_translation_b_);
			glm::mat4 model_view_projection = m_proj_ * m_view_ * model_matrix;
			m_shader_->bind();
			m_shader_->set_uniform_mat4_f("u_MVP", model_view_projection);
			renderer.draw(*m_vao_, *m_index_buffer_, *m_shader_);
		}
	}

	void TestTexture2D::on_imgui_render()
	{
		ImGui::SliderFloat3("Translation A", &m_translation_a_.x, 0.0f, 960.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::SliderFloat3("Translation B", &m_translation_b_.x, 0.0f, 960.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

}
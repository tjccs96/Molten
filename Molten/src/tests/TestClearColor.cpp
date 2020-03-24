#include "TestClearColor.h"
#include "Renderer.h"
#include "imgui/imgui.h"

namespace test {
	
	TestClearColor::TestClearColor()
		: m_clear_color_{ 0.2f, 0.3f, 0.8f, 1.0f }
	{
	}

	void TestClearColor::on_update(float delta_time)
	{
	}

	void TestClearColor::on_render()
	{
		glClearColor(m_clear_color_[0], m_clear_color_[1], m_clear_color_[2], m_clear_color_[3]);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void TestClearColor::on_imgui_render()
	{
		ImGui::ColorEdit4("Clear Color", m_clear_color_);
	}

}
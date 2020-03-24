#pragma once

#include "Test.h"

namespace test {
	
	class TestClearColor : public Test
	{
	public:
		TestClearColor();
		~TestClearColor() = default;

		void on_update(float delta_time) override;
		void on_render() override;
		void on_imgui_render() override;
	private:
		float m_clear_color_[4];
	};
}
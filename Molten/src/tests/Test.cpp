#include "Test.h"
#include "imgui/imgui.h"

namespace test {

	TestMenu::TestMenu(Test*& current_test_pointer)
		: m_current_test_(current_test_pointer)
	{
	}

	void TestMenu::on_imgui_render()
	{
		for (auto& test : m_tests_)
		{
			if (ImGui::Button(test.first.c_str()))
				m_current_test_ = test.second();
		}
	}

}
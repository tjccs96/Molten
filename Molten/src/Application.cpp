#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "tests/TestClearColor.h"
#include "tests/TestTexture2D.h"

int main(void)
{
	/* Initialize the library: GLFW */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* window = glfwCreateWindow(960, 540, "OpenGL Renderer", nullptr, nullptr);

	if (!window)
	{ 
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1); // Synchronize to monitor refresh rate

	if (glewInit() != GLEW_OK)
		std::cout << glewGetErrorString(glewInit());
	{
		
		glCall(glEnable(GL_BLEND));
		glCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		Renderer renderer;

		// ImGui stuff
		const char* glsl_version = "#version 130";
		ImGui::CreateContext();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init(glsl_version);
		ImGui::StyleColorsDark();

		test::Test* current_test = nullptr;
		auto test_menu = new test::TestMenu(current_test);
		current_test = test_menu;
		
		test_menu->register_test<test::TestClearColor>("Clear Color");
		test_menu->register_test<test::TestTexture2D>("2D Texture");

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			/* Render here */
			renderer.clear();
	
			// Start Frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			if (current_test)
			{
				current_test->on_update(0.0f);
				current_test->on_render();
				ImGui::Begin("Test");
				if (current_test != test_menu && ImGui::Button("<-"))
				{
					delete current_test;
					current_test = test_menu;
				}
				current_test->on_imgui_render();
				ImGui::End();
			}
			
			// Rendering
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
		delete current_test;
		if (current_test != test_menu)
			delete test_menu;
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}
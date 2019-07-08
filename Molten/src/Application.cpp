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

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library: GLFW */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "OpenGL Renderer", NULL, NULL);
	if (!window)
	{ 
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1); // Syncronize to monitor refresh rate

	if (glewInit() != GLEW_OK)
		std::cout << glewGetErrorString(glewInit());
	
	{
		// Define positions for the triangle to be drawn.
		float vertices[] = {
			-0.5f, -0.5f,
			 0.5f, -0.5f,
			 0.5f,  0.5f,
			-0.5f,  0.5f
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		// Create buffer, bind the buffer and get data into it.
		unsigned int vao;
		glCall(glGenVertexArrays(1, &vao));
		glCall(glBindVertexArray(vao));

		VertexArray va;
		VertexBuffer vb(vertices, 4 * 2 * sizeof(float));
		VertexBufferLayout layout;
		layout.push<float>(2);
		va.addBuffer(vb, layout);
		
		IndexBuffer ib(indices, 6);

		Shader shader("res/shaders/Basic.shader");
		shader.bind();
		shader.setUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

		va.unbind();
		vb.unbind();
		ib.unbind();
		shader.unbind();

		float r = 0.0f;
		float increment = 0.05f;

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);

			shader.bind();
			shader.setUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

			va.bind();
			ib.bind();

			glCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

			if (r > 1.0f)
				increment = -0.05f;
			else if (r < 0.0f)
				increment = 0.05f;

			r += increment;

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}
	glfwTerminate();
	return 0;
}
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define ASSERT(x) if (!(x)) __debugbreak();
#ifdef _DEBUG 
	#define glCall(x) glClearError(); x; ASSERT(glLogCall(#x, __FILE__, __LINE__)) 
#else 
	#define glCall(x) x 
#endif


static void glClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool glLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cerr << "[OpenGL error] (" << error << "): " << function << " " << 
			file << ":" << line << std::endl;
		return false;
	}
	return true;
}

struct shaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

static shaderProgramSource parseShader(const std::string& filebuff)
{
	std::ifstream stream(filebuff);

	enum class shaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	shaderType type = shaderType::NONE;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = shaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = shaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}
	return { ss[0].str(), ss[1].str() };
}

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	// Error Handling
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char)); //Carefull with this
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile " << 
			(type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader!" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}
	return id;
}

static unsigned int createShader(const std::string& vertexShader, const std::string fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

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


	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), vertices, GL_STATIC_DRAW); // or 4 * 2

	glCall(glEnableVertexAttribArray(0));
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	unsigned int indexBufferObject;
	glGenBuffers(1, &indexBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW); // or 4 * 2
	
	
	shaderProgramSource source = parseShader("res/shaders/Basic.shader");
	
	unsigned int shader = createShader(source.VertexSource, source.FragmentSource);
	glUseProgram(shader);

	glCall(int location = glGetUniformLocation(shader, "u_Color"));
	ASSERT(location != -1);
	glCall(glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f));

	glCall(glBindVertexArray(0));

	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	float r = 0.0f;
	float increment = 0.05f;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		
		glUseProgram(shader);
		glCall(glUniform4f(location, r, 0.3f, 0.8f, 1.0f));
		
		glCall(glBindVertexArray(vao));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);

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

	glDeleteProgram(shader);

	glfwTerminate();
	return 0;
}
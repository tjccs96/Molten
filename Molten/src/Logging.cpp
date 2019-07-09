#include <GLFW/glfw3.h>
#include "Logging.h"
#include <iostream>

bool glLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cerr << "[OpenGL error] (" << error << "): " << function << " " <<
			file << ":" << line << std::endl;
		return false;
	}
	return true;
}

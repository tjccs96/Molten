#pragma once

#include <GL/glew.h>

#define ASSERT(x) if (!(x)) __debugbreak();
#ifdef _DEBUG 
#define glCall(x) glClearError(); x; ASSERT(glLogCall(#x, __FILE__, __LINE__)) 
#else 
#define glCall(x) x 
#endif


void glClearError();

bool glLogCall(const char* function, const char* file, int line);

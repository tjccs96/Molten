#include "Shader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Renderer.h"


Shader::Shader(const std::string& filepath)
	: renderer_id_(0), file_path_(filepath)
{
	const ShaderProgramSource source = parse_shader(filepath);
	renderer_id_ = create_shader(source.vertex_source, source.fragment_source); 
}

Shader::~Shader()
{
	glCall(glDeleteProgram(renderer_id_));
}

ShaderProgramSource Shader::parse_shader(const std::string& filepath) const
{
	std::ifstream stream(filepath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[static_cast<int>(type)] << line << '\n';
		}
	}
	return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::compile_shader(const unsigned int type, const std::string& source)
{
	auto id = glCreateShader(type);
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

unsigned int Shader::create_shader(const std::string& vertex_shader, const std::string& fragment_shader)
{
	const auto program = glCreateProgram();
	auto vs = compile_shader(GL_VERTEX_SHADER, vertex_shader);
	auto fs = compile_shader(GL_FRAGMENT_SHADER, fragment_shader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

void Shader::bind() const
{
	glCall(glUseProgram(renderer_id_));
}

void Shader::unbind()
{
	glCall(glUseProgram(0));
}

void Shader::set_uniform1_i(const std::string& name, int value)
{
	glUniform1i(get_uniform_location(name), value);
}

void Shader::set_uniform1_f(const std::string& name, float value)
{
	glUniform1f(get_uniform_location(name), value);
}

void Shader::set_uniform4_f(const std::string& name, float v0, float v1, float v2, float v3)
{
	glUniform4f(get_uniform_location(name), v0, v1, v2, v3);
}

void Shader::set_uniform_mat4_f(const std::string& name, const glm::mat4& matrix)
{
	glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, &matrix[0][0]);
}

int Shader::get_uniform_location(const std::string& name)
{
	if (uniform_location_cache_.find(name) != uniform_location_cache_.end())
		return uniform_location_cache_[name];

	const int location = glGetUniformLocation(renderer_id_, name.c_str());
	if (location == -1)
		std::cout << "Warning uniform: '" << name << "' doesn't exist!" << std::endl;
	
	uniform_location_cache_[name] = location;
	
	return location;
}
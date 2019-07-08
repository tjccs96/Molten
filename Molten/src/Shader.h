#pragma once

#include <string>
#include <unordered_map>

struct shaderProgramSource
{
	std::string vertexSource;
	std::string fragmentSource;
};

class Shader
{
	unsigned int m_RendererID;
	std::string m_FilePath;
	std::unordered_map<std::string, int> m_UniformLocationCache;

	unsigned int getUniformLocation(const std::string& name);
	unsigned int compileShader(unsigned int type, const std::string& source);
	unsigned int createShader(const std::string& vertexShader, const std::string fragmentShader);
	shaderProgramSource parseShader(const std::string& filepath);

public:
	Shader(const std::string& filepath);
	~Shader();

	void bind() const;
	void unbind();
	
	void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
};
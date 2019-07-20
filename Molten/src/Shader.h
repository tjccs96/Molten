#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

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

	int getUniformLocation(const std::string& name);
	unsigned int compileShader(unsigned int type, const std::string& source);
	unsigned int createShader(const std::string& vertexShader, const std::string fragmentShader);
	shaderProgramSource parseShader(const std::string& filepath);

public:
	Shader(const std::string& filepath);
	~Shader();

	void bind() const;
	void unbind();
	
	void setUniform1i(const std::string& name, int value);
	void setUniform1f(const std::string& name, float value);
	void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void setUniformMat4f(const std::string& name, const glm::mat4& matrix);


};
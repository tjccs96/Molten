#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

struct ShaderProgramSource
{
	std::string vertex_source;
	std::string fragment_source;
};

class Shader
{
	unsigned int renderer_id_;
	std::string file_path_;
	std::unordered_map<std::string, int> uniform_location_cache_;

	int get_uniform_location(const std::string& name);
	unsigned int compile_shader(unsigned int type, const std::string& source);
	unsigned int create_shader(const std::string& vertex_shader, const std::string& fragment_shader);
	ShaderProgramSource parse_shader(const std::string& filepath) const;

public:
	Shader(const std::string& filepath);
	~Shader();

	void bind() const;
	void unbind();
	
	void set_uniform1_i(const std::string& name, int value);
	void set_uniform1_f(const std::string& name, float value);
	void set_uniform4_f(const std::string& name, float v0, float v1, float v2, float v3);
	void set_uniform_mat4_f(const std::string& name, const glm::mat4& matrix);

};
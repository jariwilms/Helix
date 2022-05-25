#include "stdafx.hpp"
//#include "Shader.hpp"
//
//namespace hlx
//{
//	Shader::Shader(const std::string& filepath)
//	{
//		m_identifier = glCreateProgram();
//	}
//	Shader::~Shader()
//	{
//		glDeleteProgram(m_identifier);
//	}
//
//	void Shader::bind() const
//	{
//		glUseProgram(m_identifier);
//	}
//	void Shader::unbind() const
//	{
//		glUseProgram(0);
//	}
//
//	int Shader::uniform_location(const std::string& identifier)
//	{
//		if (m_uniformLocationMap.find(identifier) != m_uniformLocationMap.end()) return m_uniformLocationMap[identifier];
//
//		int location = glGetUniformLocation(m_identifier, identifier.c_str());
//		if (location == -1) std::cout << "Insert error message of zoiets";
//		else m_uniformLocationMap[identifier] = location;
//
//		return location;
//	}
//
//	void Shader::set_bool(const std::string& identifier, bool value)
//	{
//		glUniform1i(uniform_location(identifier), (int)value);
//	}
//	void Shader::set_int(const std::string& identifier, int value)
//	{
//		glUniform1i(uniform_location(identifier), value);
//	}
//	void Shader::set_float(const std::string& identifier, float value)
//	{
//		glUniform1f(uniform_location(identifier), value);
//	}
//
//	void Shader::set_vec(const std::string& identifier, const glm::vec2& value)
//	{
//		glUniform2fv(uniform_location(identifier), 1, glm::value_ptr(value));
//	}
//	void Shader::set_vec(const std::string& identifier, const glm::vec3& value)
//	{
//		glUniform3fv(uniform_location(identifier), 1, glm::value_ptr(value));
//	}
//	void Shader::set_vec(const std::string& identifier, const glm::vec4& value)
//	{
//		glUniform4fv(uniform_location(identifier), 1, glm::value_ptr(value));
//	}
//
//	void Shader::set_mat(const std::string& identifier, const glm::mat2& value)
//	{
//		glUniformMatrix2fv(uniform_location(identifier), 1, GL_FALSE, glm::value_ptr(value));
//	}
//	void Shader::set_mat(const std::string& identifier, const glm::mat3& value)
//	{
//		glUniformMatrix3fv(uniform_location(identifier), 1, GL_FALSE, glm::value_ptr(value));
//	}
//	void Shader::set_mat(const std::string& identifier, const glm::mat4& value)
//	{
//		glUniformMatrix4fv(uniform_location(identifier), 1, GL_FALSE, glm::value_ptr(value));
//	}
//}

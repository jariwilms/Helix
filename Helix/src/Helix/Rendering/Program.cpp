#include "stdafx.hpp"

#include "Program.hpp"

namespace hlx
{
	Shader::Shader(const std::string& vertex, const std::string& geometry, const std::string& fragment)
	{
		this->programId = glCreateProgram();
	}
	Shader::~Shader()
	{
		glDeleteProgram(this->programId);
	}

	void Shader::bind() const
	{
		glUseProgram(this->programId);
	}
	void Shader::unbind() const
	{
		glUseProgram(0);
	}

	int Shader::getUniformLocation(const std::string& identifier)
	{
		if (uniformLocationMap.find(identifier) != uniformLocationMap.end()) return uniformLocationMap[identifier];

		int location = glGetUniformLocation(this->programId, identifier.c_str());
		if (location == -1) HLX_CORE_ERROR("Failed to get uniform location. Identifier: {0}", identifier);
		else this->uniformLocationMap[identifier] = location;

		return location;
	}

	void Shader::setBool(const std::string& identifier, bool value)
	{
		glUniform1i(getUniformLocation(identifier), value);
	}
	void Shader::setInt(const std::string& identifier, int value)
	{
		glUniform1i(getUniformLocation(identifier), value);
	}
	void Shader::setFloat(const std::string& identifier, float value)
	{
		glUniform1f(getUniformLocation(identifier), value);
	}

	void Shader::setVec(const std::string& identifier, const glm::vec2& value)
	{
		glUniform2fv(getUniformLocation(identifier), 1, glm::value_ptr(value));
	}
	void Shader::setVec(const std::string& identifier, const glm::vec3& value)
	{
		glUniform3fv(getUniformLocation(identifier), 1, glm::value_ptr(value));
	}
	void Shader::setVec(const std::string& identifier, const glm::vec4& value)
	{
		glUniform4fv(getUniformLocation(identifier), 1, glm::value_ptr(value));
	}

	void Shader::setMat(const std::string& identifier, const glm::mat2& value)
	{
		glUniformMatrix2fv(getUniformLocation(identifier), 1, GL_FALSE, glm::value_ptr(value));
	}
	void Shader::setMat(const std::string& identifier, const glm::mat3& value)
	{
		glUniformMatrix3fv(getUniformLocation(identifier), 1, GL_FALSE, glm::value_ptr(value));
	}
	void Shader::setMat(const std::string& identifier, const glm::mat4& value)
	{
		glUniformMatrix4fv(getUniformLocation(identifier), 1, GL_FALSE, glm::value_ptr(value));
	}
}

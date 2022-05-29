#include "stdafx.hpp"

#include "Shader.hpp"

namespace hlx
{
	Shader::Shader(const std::filesystem::path& vertex, const std::filesystem::path& fragment)
	{
		m_programId = glCreateProgram();
		HLX_CORE_ASSERT(m_programId, "Failed to create program");

		std::string vertexSource = IO::readFileToString(vertex);
		std::string fragmentSource = IO::readFileToString(fragment);

		unsigned int vertexShader = Shader::create(GL_VERTEX_SHADER, vertexSource);
		unsigned int fragmentShader = Shader::create(GL_FRAGMENT_SHADER, fragmentSource);

		glAttachShader(m_programId, vertexShader);
		glAttachShader(m_programId, fragmentShader);

		glLinkProgram(m_programId);


		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		glUseProgram(0);
	}
	Shader::Shader(const std::filesystem::path& vertex, const std::filesystem::path& geometry, const std::filesystem::path& fragment)
	{
		m_programId = glCreateProgram();
		HLX_CORE_ASSERT(m_programId, "Failed to create program");

		std::string vertexSource = IO::readFileToString("files/default.vert");
		std::string geometrySource = IO::readFileToString("files/default.geom");
		std::string fragmentSource = IO::readFileToString("files/default.frag");

		unsigned int vertexShader = Shader::create(GL_VERTEX_SHADER, vertexSource);
		unsigned int geometryShader = Shader::create(GL_GEOMETRY_SHADER, geometrySource);
		unsigned int fragmentShader = Shader::create(GL_FRAGMENT_SHADER, fragmentSource);

		glAttachShader(m_programId, vertexShader);
		glAttachShader(m_programId, geometryShader);
		glAttachShader(m_programId, fragmentShader);

		glLinkProgram(m_programId);
		checkProgramStatus(m_programId);

		glDeleteShader(vertexShader);
		glDeleteShader(geometryShader);
		glDeleteShader(fragmentShader);
	}
	Shader::~Shader()
	{
		glDeleteProgram(m_programId);
	}

	void Shader::bind() const
	{
		glUseProgram(m_programId);
	}
	void Shader::unbind() const
	{
		glUseProgram(0);
	}

	int Shader::getUniformLocation(const std::string& identifier)
	{
		if (m_uniformLocationCache.find(identifier) != m_uniformLocationCache.end()) return m_uniformLocationCache[identifier];

		int location = glGetUniformLocation(m_programId, identifier.c_str());
		if (location == -1) HLX_CORE_ERROR("Failed to get uniform location. Identifier: {0}", identifier);
		else m_uniformLocationCache[identifier] = location;

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

	void Shader::checkProgramStatus(unsigned int programId, GLenum flag)
	{
		int status{};
		glGetProgramiv(programId, flag, &status);
	
		if (status != GL_TRUE) logProgramError(programId);
	}
	void Shader::checkShaderStatus(unsigned int shaderId, GLenum flag)
	{
		int status{};
		glGetShaderiv(shaderId, flag, &status);

		if (status != GL_TRUE) logShaderError(shaderId);
	}

	void Shader::logProgramError(unsigned int programId)
	{
		int logLength{};
		glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logLength);

		std::string errorLog{};
		errorLog.resize(logLength);

		glGetProgramInfoLog(programId, logLength, &logLength, errorLog.data());
		HLX_CORE_ERROR(errorLog);
	}
	void Shader::logShaderError(unsigned int shaderId)
	{
		int logLength{};
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);

		std::string errorLog{};
		errorLog.resize(logLength);

		glGetShaderInfoLog(shaderId, logLength, &logLength, errorLog.data());
		HLX_CORE_ERROR(errorLog);
	}

	unsigned int Shader::create(GLenum type, const std::string& source)
	{
		unsigned int shader = glCreateShader(type);
		HLX_ASSERT(shader != -1, "Failed to create shader");

		Shader::compile(shader, source);

		return shader;
	}
	void Shader::compile(unsigned int shader, const std::string& source)
	{
		const char* shaderSourcePtr = source.c_str();

		glShaderSource(shader, 1, &shaderSourcePtr, nullptr);
		glCompileShader(shader);

		checkShaderStatus(shader);
	}
}

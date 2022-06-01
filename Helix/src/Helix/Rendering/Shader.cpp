#include "stdafx.hpp"
#include "Shader.hpp"

namespace hlx
{
	Shader::Shader(const std::filesystem::path& vertex, const std::filesystem::path& fragment)
		: m_programId{}, m_status {}
	{
		bool success{};

		unsigned int vertexShader = Shader::create(GL_VERTEX_SHADER);
		auto vertexSource = IO::load<std::string>(vertex);
		success = compile(vertexShader, *vertexSource);
		if (!success)
		{
			logShaderError(vertexShader);
			glDeleteShader(vertexShader);

			return;
		}

		unsigned int fragmentShader = Shader::create(GL_FRAGMENT_SHADER);
		auto fragmentSource = IO::load<std::string>(fragment);
		success = compile(fragmentShader, *fragmentSource);
		if (!success)
		{
			logShaderError(fragmentShader);
			glDeleteShader(fragmentShader);

			return;
		}

		m_programId = glCreateProgram();

		glAttachShader(m_programId, vertexShader);
		glAttachShader(m_programId, fragmentShader);

		glLinkProgram(m_programId);
		success = checkProgramStatus(m_programId);
		if (!success)
		{
			logProgramError(m_programId);
			glDeleteProgram(m_programId);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			return;
		}

		glDetachShader(m_programId, vertexShader);
		glDetachShader(m_programId, fragmentShader);

		m_status = true;
	}
	Shader::Shader(const std::filesystem::path& vertex, const std::filesystem::path& geometry, const std::filesystem::path& fragment)
		: m_programId{}, m_status {}
	{
		bool success{};

		unsigned int vertexShader = Shader::create(GL_VERTEX_SHADER);
		auto vertexSource = IO::load<std::string>(vertex);
		success = compile(vertexShader, *vertexSource);
		if (!success)
		{
			logShaderError(vertexShader);
			glDeleteShader(vertexShader);

			return;
		}

		unsigned int geometryShader = Shader::create(GL_GEOMETRY_SHADER);
		auto geometrySource = IO::load<std::string>(geometry);
		success = compile(geometryShader, *geometrySource);
		if (!success)
		{
			logShaderError(geometryShader);
			glDeleteShader(geometryShader);

			return;
		}

		unsigned int fragmentShader = Shader::create(GL_FRAGMENT_SHADER);
		auto fragmentSource = IO::load<std::string>(fragment);
		success = compile(fragmentShader, *fragmentSource);
		if (!success)
		{
			logShaderError(fragmentShader);
			glDeleteShader(fragmentShader);

			return;
		}

		m_programId = glCreateProgram();

		glAttachShader(m_programId, vertexShader);
		glAttachShader(m_programId, geometryShader);
		glAttachShader(m_programId, fragmentShader);

		glLinkProgram(m_programId);
		success = checkProgramStatus(m_programId);
		if (!success)
		{
			logProgramError(m_programId);
			glDeleteProgram(m_programId);

			glDeleteShader(vertexShader);
			glDeleteShader(geometryShader);
			glDeleteShader(fragmentShader);

			return;
		}

		glDetachShader(m_programId, vertexShader);
		glDetachShader(m_programId, geometryShader);
		glDetachShader(m_programId, fragmentShader);

		m_status = true;
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

	bool Shader::verify() const
	{
		return m_status;
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

	bool Shader::checkProgramStatus(unsigned int programId, GLenum flag)
	{
		int status{};
		glGetProgramiv(programId, flag, &status);

		return status == GL_TRUE;
	}
	bool Shader::checkShaderStatus(unsigned int shaderId, GLenum flag)
	{
		int status{};
		glGetShaderiv(shaderId, flag, &status);

		return status == GL_TRUE;
	}

	void Shader::logProgramError(unsigned int programId)
	{
		int length{};
		glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &length);

		std::string log{};
		log.reserve(++length);

		glGetProgramInfoLog(programId, length, &length, log.data());

		HLX_CORE_ERROR(log.data());
	}
	void Shader::logShaderError(unsigned int shaderId)
	{
		int length{};
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);

		std::string log{};
		log.reserve(++length);

		glGetShaderInfoLog(shaderId, length, &length, log.data());

		HLX_CORE_ERROR(log.data());
	}

	unsigned int Shader::create(GLenum type)
	{
		return glCreateShader(type);
	}
	bool Shader::compile(unsigned int shader, const std::string& source)
	{
		if (source.empty()) return false;
		const char* shaderSourcePtr = source.c_str();

		glShaderSource(shader, 1, &shaderSourcePtr, nullptr);
		glCompileShader(shader);

		return checkShaderStatus(shader);
	}
}

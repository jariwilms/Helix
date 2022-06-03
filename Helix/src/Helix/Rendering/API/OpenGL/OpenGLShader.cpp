#include "stdafx.hpp"
#include "OpenGLShader.hpp"

namespace hlx
{
	OpenGLShader::OpenGLShader(const std::filesystem::path& vertex, const std::filesystem::path& fragment)
		: m_programId{}, m_status {}
	{
		bool success{};

		unsigned int vertexOpenGLShader = OpenGLShader::create(GL_VERTEX_SHADER);
		auto vertexSource = IO::load<std::string>(vertex);
		success = compile(vertexOpenGLShader, *vertexSource);
		if (!success)
		{
			logShaderError(vertexOpenGLShader);
			glDeleteShader(vertexOpenGLShader);

			return;
		}

		unsigned int fragmentOpenGLShader = OpenGLShader::create(GL_FRAGMENT_SHADER);
		auto fragmentSource = IO::load<std::string>(fragment);
		success = compile(fragmentOpenGLShader, *fragmentSource);
		if (!success)
		{
			logShaderError(fragmentOpenGLShader);
			glDeleteShader(fragmentOpenGLShader);

			return;
		}

		m_programId = glCreateProgram();

		glAttachShader(m_programId, vertexOpenGLShader);
		glAttachShader(m_programId, fragmentOpenGLShader);

		glLinkProgram(m_programId);
		success = checkProgramStatus(m_programId);
		if (!success)
		{
			logProgramError(m_programId);
			glDeleteProgram(m_programId);

			glDeleteShader(vertexOpenGLShader);
			glDeleteShader(fragmentOpenGLShader);

			return;
		}

		glDetachShader(m_programId, vertexOpenGLShader);
		glDetachShader(m_programId, fragmentOpenGLShader);

		m_status = true;
	}
	OpenGLShader::OpenGLShader(const std::filesystem::path& vertex, const std::filesystem::path& geometry, const std::filesystem::path& fragment)
		: m_programId{}, m_status {}
	{
		bool success{};

		unsigned int vertexOpenGLShader = OpenGLShader::create(GL_VERTEX_SHADER);
		auto vertexSource = IO::load<std::string>(vertex);
		success = compile(vertexOpenGLShader, *vertexSource);
		if (!success)
		{
			logShaderError(vertexOpenGLShader);
			glDeleteShader(vertexOpenGLShader);

			return;
		}

		unsigned int geometryOpenGLShader = OpenGLShader::create(GL_GEOMETRY_SHADER);
		auto geometrySource = IO::load<std::string>(geometry);
		success = compile(geometryOpenGLShader, *geometrySource);
		if (!success)
		{
			logShaderError(geometryOpenGLShader);
			glDeleteShader(geometryOpenGLShader);

			return;
		}

		unsigned int fragmentOpenGLShader = OpenGLShader::create(GL_FRAGMENT_SHADER);
		auto fragmentSource = IO::load<std::string>(fragment);
		success = compile(fragmentOpenGLShader, *fragmentSource);
		if (!success)
		{
			logShaderError(fragmentOpenGLShader);
			glDeleteShader(fragmentOpenGLShader);

			return;
		}

		m_programId = glCreateProgram();

		glAttachShader(m_programId, vertexOpenGLShader);
		glAttachShader(m_programId, geometryOpenGLShader);
		glAttachShader(m_programId, fragmentOpenGLShader);

		glLinkProgram(m_programId);
		success = checkProgramStatus(m_programId);
		if (!success)
		{
			logProgramError(m_programId);
			glDeleteProgram(m_programId);

			glDeleteShader(vertexOpenGLShader);
			glDeleteShader(geometryOpenGLShader);
			glDeleteShader(fragmentOpenGLShader);

			return;
		}

		glDetachShader(m_programId, vertexOpenGLShader);
		glDetachShader(m_programId, geometryOpenGLShader);
		glDetachShader(m_programId, fragmentOpenGLShader);

		m_status = true;
	}
	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_programId);
	}

	void OpenGLShader::bind() const
	{
		glUseProgram(m_programId);
	}
	void OpenGLShader::unbind() const
	{
		glUseProgram(0);
	}

	int OpenGLShader::getUniformLocation(const std::string& identifier)
	{
		if (m_uniformLocationCache.find(identifier) != m_uniformLocationCache.end()) return m_uniformLocationCache[identifier];

		int location = glGetUniformLocation(m_programId, identifier.c_str());
		if (location == -1) HLX_CORE_ERROR("Failed to get uniform location. Identifier: {0}", identifier);
		else m_uniformLocationCache[identifier] = location;

		return location;
	}

	void OpenGLShader::setBool(const std::string& identifier, bool value)
	{
		glUniform1i(getUniformLocation(identifier), value);
	}
	void OpenGLShader::setInt(const std::string& identifier, int value)
	{
		glUniform1i(getUniformLocation(identifier), value);
	}
	void OpenGLShader::setFloat(const std::string& identifier, float value)
	{
		glUniform1f(getUniformLocation(identifier), value);
	}

	void OpenGLShader::setVec(const std::string& identifier, const glm::vec2& value)
	{
		glUniform2fv(getUniformLocation(identifier), 1, glm::value_ptr(value));
	}
	void OpenGLShader::setVec(const std::string& identifier, const glm::vec3& value)
	{
		glUniform3fv(getUniformLocation(identifier), 1, glm::value_ptr(value));
	}
	void OpenGLShader::setVec(const std::string& identifier, const glm::vec4& value)
	{
		glUniform4fv(getUniformLocation(identifier), 1, glm::value_ptr(value));
	}

	void OpenGLShader::setMat(const std::string& identifier, const glm::mat2& value)
	{
		glUniformMatrix2fv(getUniformLocation(identifier), 1, GL_FALSE, glm::value_ptr(value));
	}
	void OpenGLShader::setMat(const std::string& identifier, const glm::mat3& value)
	{
		glUniformMatrix3fv(getUniformLocation(identifier), 1, GL_FALSE, glm::value_ptr(value));
	}
	void OpenGLShader::setMat(const std::string& identifier, const glm::mat4& value)
	{
		glUniformMatrix4fv(getUniformLocation(identifier), 1, GL_FALSE, glm::value_ptr(value));
	}

	bool OpenGLShader::checkProgramStatus(unsigned int programId)
	{
		int status{};
		glGetProgramiv(programId, GL_LINK_STATUS, &status);

		return status == GL_TRUE;
	}
	bool OpenGLShader::checkShaderStatus(unsigned int shaderId)
	{
		int status{};
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);

		return status == GL_TRUE;
	}

	void OpenGLShader::logProgramError(unsigned int programId)
	{
		int length{};
		glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &length);

		std::string log{};
		log.reserve(++length);

		glGetProgramInfoLog(programId, length, &length, log.data());

		HLX_CORE_ERROR(log.data());
	}
	void OpenGLShader::logShaderError(unsigned int shaderId)
	{
		int length{};
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);

		std::string log{};
		log.reserve(++length);

		glGetShaderInfoLog(shaderId, length, &length, log.data());

		HLX_CORE_ERROR(log.data());
	}

	unsigned int OpenGLShader::create(unsigned int type)
	{
		return glCreateShader(type);
	}
	bool OpenGLShader::compile(unsigned int shaderId, const std::string& source)
	{
		if (source.empty()) return false;
		const char* shaderSourcePtr = source.c_str();

		glShaderSource(shaderId, 1, &shaderSourcePtr, nullptr);
		glCompileShader(shaderId);

		return checkShaderStatus(shaderId);
	}
}

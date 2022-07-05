#include "stdafx.hpp"
#include "OpenGLShader.hpp"

namespace hlx
{
	OpenGLShader::OpenGLShader(const std::string& vertex, const std::string& fragment)
		: m_programId{}, m_status {}
	{
		bool success{};

		unsigned int vertexShaderId = OpenGLShader::create(GL_VERTEX_SHADER);
		success = compile(vertexShaderId, vertex);
		if (!success)
		{
			logShaderError(vertexShaderId);
			glDeleteShader(vertexShaderId);

			return;
		}

		unsigned int fragmentShaderId = OpenGLShader::create(GL_FRAGMENT_SHADER);
		success = compile(fragmentShaderId, fragment);
		if (!success)
		{
			logShaderError(fragmentShaderId);
			glDeleteShader(fragmentShaderId);

			return;
		}

		m_programId = glCreateProgram();

		glAttachShader(m_programId, vertexShaderId);
		glAttachShader(m_programId, fragmentShaderId);

		glLinkProgram(m_programId);
		success = checkProgramStatus(m_programId);
		if (!success)
		{
			logProgramError(m_programId);
			glDeleteProgram(m_programId);

			glDeleteShader(vertexShaderId);
			glDeleteShader(fragmentShaderId);

			return;
		}

		glDetachShader(m_programId, vertexShaderId);
		glDetachShader(m_programId, fragmentShaderId);

		m_status = true;
	}
	OpenGLShader::OpenGLShader(const std::string& vertex, const std::string& geometry, const std::string& fragment)
		: m_programId{}, m_status {}
	{
		bool success{};

		unsigned int vertexShaderId = OpenGLShader::create(GL_VERTEX_SHADER);
		success = compile(vertexShaderId, vertex);
		if (!success)
		{
			logShaderError(vertexShaderId);
			glDeleteShader(vertexShaderId);

			return;
		}

		unsigned int geometryShaderId = OpenGLShader::create(GL_GEOMETRY_SHADER);
		success = compile(geometryShaderId, geometry);
		if (!success)
		{
			logShaderError(geometryShaderId);
			glDeleteShader(geometryShaderId);

			return;
		}

		unsigned int fragmentShaderId = OpenGLShader::create(GL_FRAGMENT_SHADER);
		success = compile(fragmentShaderId, fragment);
		if (!success)
		{
			logShaderError(fragmentShaderId);
			glDeleteShader(fragmentShaderId);

			return;
		}

		m_programId = glCreateProgram();

		glAttachShader(m_programId, vertexShaderId);
		glAttachShader(m_programId, geometryShaderId);
		glAttachShader(m_programId, fragmentShaderId);

		glLinkProgram(m_programId);
		success = checkProgramStatus(m_programId);
		if (!success)
		{
			logProgramError(m_programId);
			glDeleteProgram(m_programId);

			glDeleteShader(vertexShaderId);
			glDeleteShader(geometryShaderId);
			glDeleteShader(fragmentShaderId);

			return;
		}

		glDetachShader(m_programId, vertexShaderId);
		glDetachShader(m_programId, geometryShaderId);
		glDetachShader(m_programId, fragmentShaderId);

		m_status = true;
	}
	OpenGLShader::~OpenGLShader()
	{
		if (s_activeProgramId == m_programId) s_activeProgramId = 0;
		
		glDeleteProgram(m_programId);
	}

	void OpenGLShader::bind() const
	{
		if (s_activeProgramId == m_programId) 
			return;
			
		glUseProgram(m_programId);
		s_activeProgramId = m_programId;
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

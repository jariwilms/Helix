#include "stdafx.hpp"
#include "OpenGLShader.hpp"

namespace hlx
{
	OpenGLShader::OpenGLShader(const std::string& vertex, const std::string& fragment)
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

		m_id = glCreateProgram();

		glAttachShader(m_id, vertexShaderId);
		glAttachShader(m_id, fragmentShaderId);

		glLinkProgram(m_id);
		success = checkProgramStatus(m_id);
		if (!success)
		{
			logProgramError(m_id);
			glDeleteProgram(m_id);

			glDeleteShader(vertexShaderId);
			glDeleteShader(fragmentShaderId);

			return;
		}

		glDetachShader(m_id, vertexShaderId);
		glDetachShader(m_id, fragmentShaderId);
	}
	OpenGLShader::OpenGLShader(const std::string& vertex, const std::string& geometry, const std::string& fragment)
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

		m_id = glCreateProgram();

		glAttachShader(m_id, vertexShaderId);
		glAttachShader(m_id, geometryShaderId);
		glAttachShader(m_id, fragmentShaderId);

		glLinkProgram(m_id);
		success = checkProgramStatus(m_id);
		if (!success)
		{
			logProgramError(m_id);
			glDeleteProgram(m_id);

			glDeleteShader(vertexShaderId);
			glDeleteShader(geometryShaderId);
			glDeleteShader(fragmentShaderId);

			return;
		}

		glDetachShader(m_id, vertexShaderId);
		glDetachShader(m_id, geometryShaderId);
		glDetachShader(m_id, fragmentShaderId);
	}
	OpenGLShader::~OpenGLShader()
	{
		if (s_boundProgramId == m_id) s_boundProgramId = 0;
		
		glDeleteProgram(m_id);
	}

	bool OpenGLShader::bind() const
	{
		//if (s_boundProgramId == m_id)
			//return false;
			
		glUseProgram(m_id);
		s_boundProgramId = m_id;

		return true;
	}
	void OpenGLShader::unbind() const
	{
		glUseProgram(0);
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

	void OpenGLShader::setUniformBuffer(const std::string& identifier, size_t size, const void* data)
	{
		getUniformBuffer(identifier)->setSubData(size, data);
	}
	void OpenGLShader::setUniformBuffer(const std::string& identifier, size_t size, unsigned int offset, const void* data)
	{
		getUniformBuffer(identifier)->setSubData(size, offset, data);
	}

	int OpenGLShader::getUniformLocation(const std::string& identifier)
	{
		if (m_uniformLocationCache.find(identifier) != m_uniformLocationCache.end()) return m_uniformLocationCache.at(identifier);

		int location = glGetUniformLocation(m_id, identifier.c_str());
		
		if (location != -1) m_uniformLocationCache.insert(std::make_pair(identifier, location)); 
		else HLX_CORE_ERROR("Failed to get uniform location. Identifier: {0}", identifier);

		return location;
	}
	int OpenGLShader::getUniformBlockIndex(const std::string& identifier)
	{
		if (m_uniformBlockIndexCache.find(identifier) != m_uniformBlockIndexCache.end()) return m_uniformBlockIndexCache.at(identifier);

		int index = glGetUniformBlockIndex(m_id, identifier.c_str());
		
		if (index != -1) m_uniformBlockIndexCache.insert(std::make_pair(identifier, index)); 
		else HLX_CORE_ERROR("Failed to get uniform block location. Identifier: {0}", identifier);
		
		return index;
	}
	
	std::shared_ptr<hlx::UniformBuffer> OpenGLShader::getUniformBuffer(const std::string& identifier)
	{
		if (s_uniformBufferCache.find(identifier) != s_uniformBufferCache.end()) return s_uniformBufferCache.at(identifier);
		
		return createUniformBuffer(identifier);
	}
	std::shared_ptr<hlx::UniformBuffer> OpenGLShader::createUniformBuffer(const std::string& identifier)
	{
		auto blockIndex = getUniformBlockIndex(identifier);
		auto blockBinding = static_cast<int>(s_uniformBufferCache.size());
		int blockSize{};

		glGetActiveUniformBlockiv(m_id, blockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);
		auto pair = s_uniformBufferCache.insert(std::make_pair(identifier, UniformBuffer::create(blockIndex, blockBinding, blockSize)));

		return pair.first->second;
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

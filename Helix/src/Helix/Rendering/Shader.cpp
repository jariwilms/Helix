#include "stdafx.hpp"
#include "Shader.hpp"

#include "API/OpenGL/Shader/OpenGLShader.hpp"

namespace hlx
{
	std::shared_ptr<Shader> Shader::create(const std::filesystem::path& vertex, const std::filesystem::path& fragment)
	{
		return std::make_shared<OpenGLShader>(vertex, fragment);
	}

	std::shared_ptr<Shader> Shader::create(const std::filesystem::path& vertex, const std::filesystem::path& geometry, const std::filesystem::path& fragment)
	{
		return std::make_shared<OpenGLShader>(vertex, geometry, fragment);
	}

	bool Shader::verify() const
	{
		return m_status;
	}
}

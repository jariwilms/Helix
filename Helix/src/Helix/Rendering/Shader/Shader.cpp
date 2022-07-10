#include "stdafx.hpp"
#include "Shader.hpp"

#include "Helix/Rendering/API/OpenGL/Shader/OpenGLShader.hpp"

namespace hlx
{
	std::shared_ptr<Shader> Shader::create(const std::filesystem::path& path)
	{
		return IO::load<Shader>(path);
	}
	std::shared_ptr<Shader> Shader::create(const std::string& vertex, const std::string& fragment)
	{
		return std::make_shared<OpenGLShader>(vertex, fragment);
	}
	std::shared_ptr<Shader> Shader::create(const std::string& vertex, const std::string& geometry, const std::string& fragment)
	{
		return std::make_shared<OpenGLShader>(vertex, geometry, fragment);
	}
}

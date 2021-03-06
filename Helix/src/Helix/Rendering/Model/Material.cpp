#include "stdafx.hpp"
#include "Material.hpp"

namespace hlx
{
	Material::Material(const std::string& name, std::shared_ptr<Shader> shader)
		: m_name{ name }, m_shader{ shader }, m_baseColor{ 1.0f }, m_emissionColor{ 0.0f }, m_metallicity{ 0.0f }, m_roughness{ 0.0f }, m_opacity{ 1.0f }
	{
		auto whiteTexture = IO::load<Texture>("textures/white.png");
		m_albedo = whiteTexture;
		m_normal = whiteTexture;
		m_specular = whiteTexture;
	}
}
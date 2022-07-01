#include "stdafx.hpp"
#include "Material.hpp"

namespace hlx
{
	Material::Material(std::shared_ptr<Shader> shader)
		: m_baseColor{ 1.0f }, m_emissionColor{ 0.0f }, m_metallicity{ 0.0f }, m_roughness{ 0.0f }, m_opacity{ 1.0f }, m_shader{ shader }
	{
		auto white = IO::load<Texture>("textures/white.png");

		m_albedo = white;
		m_normal = white;
		m_specular = white;
	}
}
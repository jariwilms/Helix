#pragma once

#include "stdafx.hpp"

#include "glm/glm.hpp"

#include "Helix/Rendering/Shader/Shader.hpp"
#include "Helix/Scene/Camera/Camera.hpp"

namespace hlx
{
	class Material
	{
	public:
		Material();
		explicit Material(std::shared_ptr<Shader> shader);

		void use() const 
		{ 
			m_shader->bind();

			m_shader->setVec("u_baseColor", m_baseColor);
			m_albedo->bind();

			//m_shader->setFloat("u_opacity", m_opacity);
		}

		inline std::shared_ptr<Shader> getShader() { return m_shader; }

		inline const glm::vec3& getBaseColor() const { return m_baseColor; }
		inline const glm::vec3& getEmissionColor() const { return m_emissionColor; }

		inline float getMetallicity() const { return m_metallicity; }
		inline float getRoughness() const { return m_roughness; }
		inline float getOpacity() const { return m_opacity; }

		inline std::shared_ptr<Texture> getAlbedo() const { return m_albedo; }
		inline std::shared_ptr<Texture> getNormal() const { return m_normal; }
		inline std::shared_ptr<Texture> getSpecular() const { return m_specular; }

		inline void setBaseColor(glm::vec3 baseColor) { m_baseColor = glm::clamp(baseColor, glm::vec3{ 0.0f }, glm::vec3{ 1.0f }); }
		inline void setEmissionColor(glm::vec3 emissionColor) { m_emissionColor = glm::clamp(emissionColor, glm::vec3{ 0.0f }, glm::vec3{ 1.0f }); }

		inline void setMetallicity(float metallicity) { m_metallicity = metallicity; }
		inline void setRoughness(float roughness) { m_roughness = roughness; }
		inline void setOpacity(float opacity) { m_opacity = opacity; }

		inline void setAlbedo(std::shared_ptr<Texture> albedo) { m_albedo = albedo; }
		inline void setNormal(std::shared_ptr<Texture> normal) { m_normal = normal; }
		inline void setSpecular(std::shared_ptr<Texture> specular) { m_specular = specular; }

	private:
		std::shared_ptr<Shader> m_shader;

		glm::vec3 m_baseColor;
		glm::vec3 m_emissionColor;

		float m_metallicity;
		float m_roughness;
		float m_opacity;

		std::shared_ptr<Texture> m_albedo;
		std::shared_ptr<Texture> m_normal;
		std::shared_ptr<Texture> m_specular;
	};
}

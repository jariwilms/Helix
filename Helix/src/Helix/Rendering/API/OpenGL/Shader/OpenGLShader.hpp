#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Helix/Rendering/Shader/Shader.hpp"

namespace hlx
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::filesystem::path& vertex, const std::filesystem::path& fragment);
		OpenGLShader(const std::filesystem::path& vertex, const std::filesystem::path& geometry, const std::filesystem::path& fragment);
		~OpenGLShader();

		void bind() const override;
		void unbind() const override;

		int getUniformLocation(const std::string& id) override;

		void setBool(const std::string& identifier, bool value) override;
		void setInt(const std::string& identifier, int value) override;
		void setFloat(const std::string& identifier, float value) override;

		void setVec(const std::string& identifier, const glm::vec2& value) override;
		void setVec(const std::string& identifier, const glm::vec3& value) override;
		void setVec(const std::string& identifier, const glm::vec4& value) override;

		void setMat(const std::string& identifier, const glm::mat2& value) override;
		void setMat(const std::string& identifier, const glm::mat3& value) override;
		void setMat(const std::string& identifier, const glm::mat4& value) override;

	private:
		bool checkProgramStatus(unsigned int programId) override;
		bool checkShaderStatus(unsigned int shaderId) override;

		void logProgramError(unsigned int programId) override;
		void logShaderError(unsigned int shaderId) override;

		unsigned int create(unsigned int type) override;
		bool compile(unsigned int shaderId, const std::string& source) override;

		bool m_status;;
		unsigned int m_programId;
		std::unordered_map<std::string, int> m_uniformLocationCache;
	};
}

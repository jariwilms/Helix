#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace hlx
{
	class Shader
	{
	public:
		Shader(const std::filesystem::path& vertex, const std::filesystem::path& fragment);
		Shader(const std::filesystem::path& vertex, const std::filesystem::path& geometry, const std::filesystem::path& fragment);
		~Shader();

		void bind() const;
		void unbind() const;

		bool verify() const;
		int getUniformLocation(const std::string& id);

		void setBool(const std::string& identifier, bool value);
		void setInt(const std::string& identifier, int value);
		void setFloat(const std::string& identifier, float value);

		void setVec(const std::string& identifier, const glm::vec2& value);
		void setVec(const std::string& identifier, const glm::vec3& value);
		void setVec(const std::string& identifier, const glm::vec4& value);

		void setMat(const std::string& identifier, const glm::mat2& value);
		void setMat(const std::string& identifier, const glm::mat3& value);
		void setMat(const std::string& identifier, const glm::mat4& value);

	private:
		static bool checkProgramStatus(unsigned int programId, GLenum flag = GL_LINK_STATUS);
		static bool checkShaderStatus(unsigned int shaderId, GLenum flag = GL_COMPILE_STATUS);

		static void logProgramError(unsigned int programId);
		static void logShaderError(unsigned int shaderId);

		unsigned int create(GLenum type);
		bool compile(unsigned int shader, const std::string& source);

		bool m_status;;
		unsigned int m_programId;
		std::unordered_map<std::string, int> m_uniformLocationCache;
	};
}

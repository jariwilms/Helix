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
		virtual ~Shader() = default;

		static std::shared_ptr<Shader> create(const std::filesystem::path& vertex, const std::filesystem::path& fragment);
		static std::shared_ptr<Shader> create(const std::filesystem::path& vertex, const std::filesystem::path& geometry, const std::filesystem::path& fragment);

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		bool verify() const;
		virtual int getUniformLocation(const std::string& id) = 0;

		virtual void setBool(const std::string& identifier, bool value) = 0;
		virtual void setInt(const std::string& identifier, int value) = 0;
		virtual void setFloat(const std::string& identifier, float value) = 0;

		virtual void setVec(const std::string& identifier, const glm::vec2& value) = 0;
		virtual void setVec(const std::string& identifier, const glm::vec3& value) = 0;
		virtual void setVec(const std::string& identifier, const glm::vec4& value) = 0;

		virtual void setMat(const std::string& identifier, const glm::mat2& value) = 0;
		virtual void setMat(const std::string& identifier, const glm::mat3& value) = 0;
		virtual void setMat(const std::string& identifier, const glm::mat4& value) = 0;

	protected:
		Shader() : m_status{}, m_programId{} {}

		virtual bool checkProgramStatus(unsigned int programId) = 0;
		virtual bool checkShaderStatus(unsigned int shaderId) = 0;

		virtual void logProgramError(unsigned int programId) = 0;
		virtual void logShaderError(unsigned int shaderId) = 0;

		virtual unsigned int create(unsigned int type) = 0;
		virtual bool compile(unsigned int shaderId, const std::string& source) = 0;

		bool m_status;
		unsigned int m_programId;

		std::unordered_map<std::string, int> m_uniformLocationCache;
	};
}

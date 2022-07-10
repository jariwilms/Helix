#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Helix/Rendering/Object/UniformBuffer.hpp"

namespace hlx
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		static std::shared_ptr<Shader> create(const std::filesystem::path& path);
		static std::shared_ptr<Shader> create(const std::string& vertex, const std::string& fragment);
		static std::shared_ptr<Shader> create(const std::string& vertex, const std::string& geometry, const std::string& fragment);

		virtual bool bind() const = 0;
		virtual void unbind() const = 0;

		static inline unsigned int getBoundShaderId() { return s_boundProgramId; }

		virtual void setBool(const std::string& identifier, bool value) = 0;
		virtual void setInt(const std::string& identifier, int value) = 0;
		virtual void setFloat(const std::string& identifier, float value) = 0;

		virtual void setVec(const std::string& identifier, const glm::vec2& value) = 0;
		virtual void setVec(const std::string& identifier, const glm::vec3& value) = 0;
		virtual void setVec(const std::string& identifier, const glm::vec4& value) = 0;

		virtual void setMat(const std::string& identifier, const glm::mat2& value) = 0;
		virtual void setMat(const std::string& identifier, const glm::mat3& value) = 0;
		virtual void setMat(const std::string& identifier, const glm::mat4& value) = 0;

		virtual void setUniformBuffer(const std::string& identifier, size_t size, const void* data) = 0;
		virtual void setUniformBuffer(const std::string& identifier, size_t size, unsigned int offset, const void* data) = 0;

	protected:
		Shader() : m_id{} {}
		
		virtual int getUniformLocation(const std::string& identifier) = 0;
		virtual int getUniformBlockIndex(const std::string& identifier) = 0;
		
		virtual std::shared_ptr<UniformBuffer> getUniformBuffer(const std::string& identifier) = 0;
		virtual std::shared_ptr<UniformBuffer> createUniformBuffer(const std::string& identifier) = 0;
		
		virtual bool checkProgramStatus(unsigned int programId) = 0;
		virtual bool checkShaderStatus(unsigned int shaderId) = 0;

		virtual void logProgramError(unsigned int programId) = 0;
		virtual void logShaderError(unsigned int shaderId) = 0;

		virtual unsigned int create(unsigned int type) = 0;
		virtual bool compile(unsigned int shaderId, const std::string& source) = 0;

		unsigned int m_id;
		static inline unsigned int s_boundProgramId = 0;

		std::unordered_map<std::string, int> m_uniformLocationCache;
		std::unordered_map<std::string, int> m_uniformBlockIndexCache;
		static inline std::unordered_map<std::string, std::shared_ptr<UniformBuffer>> s_uniformBufferCache;
	};
}

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
		OpenGLShader(const std::string& vertex, const std::string& fragment);
		OpenGLShader(const std::string& vertex, const std::string& geometry, const std::string& fragment);
		~OpenGLShader();

		void bind() const override;
		void unbind() const override;
		bool isBound() const override;

		int getUniformLocation(const std::string& id) override;
		int getUniformBlockIndex(const std::string& identifier) override;

		void setBool(const std::string& identifier, bool value) override;
		void setInt(const std::string& identifier, int value) override;
		void setFloat(const std::string& identifier, float value) override;

		void setVec(const std::string& identifier, const glm::vec2& value) override;
		void setVec(const std::string& identifier, const glm::vec3& value) override;
		void setVec(const std::string& identifier, const glm::vec4& value) override;

		void setMat(const std::string& identifier, const glm::mat2& value) override;
		void setMat(const std::string& identifier, const glm::mat3& value) override;
		void setMat(const std::string& identifier, const glm::mat4& value) override;

		void setUniformBuffer(const std::string& identifier, size_t size, const void* data) override;
		void setUniformBuffer(const std::string& identifier, size_t size, unsigned int offset, const void* data) override;
		
		std::shared_ptr<UniformBuffer> getUniformBuffer(const std::string& identifier) override;
		std::shared_ptr<UniformBuffer> createUniformBuffer(const std::string& identifier) override;

	private:
		bool checkProgramStatus(unsigned int programId) override; //Todo: move naar base shader als virtual?
		bool checkShaderStatus(unsigned int shaderId) override;

		void logProgramError(unsigned int programId) override;
		void logShaderError(unsigned int shaderId) override;

		unsigned int create(unsigned int type) override;
		bool compile(unsigned int shaderId, const std::string& source) override;
	};
}

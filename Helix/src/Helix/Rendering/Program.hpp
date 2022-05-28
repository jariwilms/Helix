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
		Shader(const std::string& vertex, const std::string& geometry, const std::string& fragment);
		~Shader();

		void bind() const;
		void unbind() const;

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
		unsigned int programId;
		std::unordered_map<std::string, int> uniformLocationMap;
	};
}

//#pragma once
//
//#include "GLAD/glad.h"
//#include "GLFW/glfw3.h"
//#include "GLM/glm.hpp"
//#include "GLM/gtc/type_ptr.hpp"
//
//namespace hlx
//{
//	class Shader
//	{
//	public:
//		Shader(const std::string& filepath);
//		~Shader();
//
//		void bind() const;
//		void unbind() const;
//
//		int uniform_location(const std::string& identifier);
//
//		void set_bool(const std::string& identifier, bool value);
//		void set_int(const std::string& identifier, int value);
//		void set_float(const std::string& identifier, float value);
//
//		void set_vec(const std::string& identifier, const glm::vec2& value);
//		void set_vec(const std::string& identifier, const glm::vec3& value);
//		void set_vec(const std::string& identifier, const glm::vec4& value);
//
//		void set_mat(const std::string& identifier, const glm::mat2& value);
//		void set_mat(const std::string& identifier, const glm::mat3& value);
//		void set_mat(const std::string& identifier, const glm::mat4& value);
//
//	private:
//		unsigned int m_identifier;
//		std::unordered_map<std::string, int> m_uniformLocationMap;
//	};
//}

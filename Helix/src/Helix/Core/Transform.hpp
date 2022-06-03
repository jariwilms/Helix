#pragma once

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

namespace hlx
{
	class Transform
	{
	public:
		Transform(glm::vec3 position = glm::vec3{}, glm::vec3 rotation = glm::vec3{}, glm::vec3 scale = glm::vec3{});
		~Transform() = default;

		void translate(const glm::vec3& translation);
		void translate(float x, float y, float z);

		void rotate(float angle, const glm::vec3& axes);
		void rotate(float angle, float x, float y, float z);

		void dilate(const glm::vec3& dilation);
		void dilate(float x, float y, float z);

		static glm::vec3 translate(const glm::vec3& position, const glm::vec3& translation);
		static glm::vec3 translate(float xPosition, float yPosition, float zPosition, float xTranslation, float yTranslation, float zTranslation);

		static glm::vec3 rotate(const glm::vec3& rotation, float angle, const glm::vec3& axes);
		static glm::vec3 rotate(float xRotation, float yRotation, float zRotation, float angle, float xAxis, float yAxis, float zAxis);

		static glm::vec3 dilate(const glm::vec3& scale, const glm::vec3& dilation);
		static glm::vec3 dilate(float xScale, float yScale, float zScale, float xDilation, float yDilation, float zDilation);

		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
	};
}

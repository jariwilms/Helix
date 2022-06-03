#include "stdafx.hpp"
#include "Transform.hpp"

namespace hlx
{
	Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
		: position{ position }, rotation{ rotation }, scale{ scale } {}

	void Transform::translate(const glm::vec3& translation)
	{
		position += translation;
	}
	void Transform::translate(float x, float y, float z)
	{
		translate(glm::vec3{ x, y, z });
	}

	void Transform::rotate(float angle, const glm::vec3& axes)
	{
		glm::mat4 rotationMatrix = glm::rotate(glm::mat4{ 1.0f }, angle, axes);
		rotation = rotationMatrix * glm::vec4{ rotation, 1.0f };
	}
	void Transform::rotate(float angle, float x, float y, float z)
	{
		rotate(angle, glm::vec3{ x, y, z });
	}

	void Transform::dilate(const glm::vec3& dilation)
	{
		scale *= dilation;
	}
	void Transform::dilate(float x, float y, float z)
	{
		dilate(glm::vec3{ x, y, z });
	}

	glm::vec3 Transform::translate(const glm::vec3& position, const glm::vec3& translation)
	{
		return position + translation;
	}
	glm::vec3 Transform::translate(float xPosition, float yPosition, float zPosition, float xTranslation, float yTranslation, float zTranslation)
	{
		return translate(glm::vec3{ xPosition, yPosition, zPosition }, glm::vec3{ xTranslation, yTranslation, zTranslation });
	}

	glm::vec3 Transform::rotate(const glm::vec3& rotation, float angle, const glm::vec3& axes)
	{
		glm::mat4 rotationMatrix = glm::rotate(glm::mat4{ 1.0f }, angle, axes);
		return rotationMatrix * glm::vec4{ rotation, 1.0f };
	}
	glm::vec3 Transform::rotate(float xRotation, float yRotation, float zRotation, float angle, float xAxis, float yAxis, float zAxis)
	{
		return rotate(glm::vec3{ xRotation, yRotation, zRotation }, angle, glm::vec3{ xAxis, yAxis, zAxis });
	}

	glm::vec3 Transform::dilate(const glm::vec3& scale, const glm::vec3& dilation)
	{
		return scale * dilation;
	}
	glm::vec3 Transform::dilate(float xScale, float yScale, float zScale, float xDilation, float yDilation, float zDilation)
	{
		return dilate(glm::vec3{ xScale, yScale, zScale }, glm::vec3{ xDilation, yDilation, zDilation });
	}
}

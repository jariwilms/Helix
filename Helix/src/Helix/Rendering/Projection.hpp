#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace hlx
{
	enum class ProjectionType
	{
		Orthographic,
		Perspective,
	};

	using OrthographicProjection = struct OrthographicProjection;
	struct OrthographicProjection
	{
		OrthographicProjection(float leftPlane = -1.0f, float rightPlane = 1.0f, float bottomPlane = -1.0f, float topPlane = 1.0f)
			: leftPlane{ leftPlane }, rightPlane{ rightPlane }, bottomPlane{ bottomPlane }, topPlane{ topPlane } {}

		static glm::mat4 create(OrthographicProjection projection)
		{
			return glm::ortho(projection.leftPlane, projection.rightPlane, projection.bottomPlane, projection.topPlane);
		}

		static glm::mat4 create(float leftPlane, float rightPlane, float bottomPlane, float topPlane)
		{
			return glm::ortho(leftPlane, rightPlane, bottomPlane, topPlane);
		}

		float leftPlane;
		float rightPlane;
		float bottomPlane;
		float topPlane;
	};

	using PerspectiveProjection = struct PerspectiveProjection;
	struct PerspectiveProjection
	{
		PerspectiveProjection(float fov = 45.0f, float aspectRatio = 1.78f, float nearPlane = 0.01f, float farPlane = 100.0f)
			: fov{ fov }, aspectRatio{ aspectRatio }, nearPlane{ nearPlane }, farPlane{ farPlane } {}

		static glm::mat4 create(PerspectiveProjection projection)
		{
			return glm::perspective(projection.fov, projection.aspectRatio, projection.nearPlane, projection.farPlane);
		}

		static glm::mat4 create(float fov, float aspectRatio, float nearPlane, float farPlane)
		{
			return glm::perspective(fov, aspectRatio, nearPlane, farPlane);
		}

		float fov;
		float aspectRatio;
		float nearPlane;
		float farPlane;
	};
}

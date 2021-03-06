#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace hlx
{
	class Projection
	{
	public:
		enum class Type
		{
			Orthographic,
			Perspective,
		};

		struct OrthographicSettings
		{
			OrthographicSettings(float leftPlane = -1.0f, float rightPlane = 1.0f, float bottomPlane = -1.0f, float topPlane = 1.0f, float nearPlane = 0.1f, float farPlane = 100.0f)
				: leftPlane{ leftPlane }, rightPlane{ rightPlane }, bottomPlane{ bottomPlane }, topPlane{ topPlane }, nearPlane{ nearPlane }, farPlane{ farPlane }, spread{ 0.0f } {}

			float leftPlane;
			float rightPlane;
			float bottomPlane;
			float topPlane;
			float nearPlane;
			float farPlane;

			float spread;
		};

		struct PerspectiveSettings
		{
			PerspectiveSettings(float fov = 45.0f, float aspectRatio = 1.0f, float nearPlane = 0.1f, float farPlane = 100.0f)
				: fov{ fov }, aspectRatio{ aspectRatio }, nearPlane{ nearPlane }, farPlane{ farPlane } {}

			float fov;
			float aspectRatio;
			float nearPlane;
			float farPlane;
		};

		static glm::mat4 createOrthographic(OrthographicSettings projection)
		{
			return glm::ortho(projection.leftPlane - projection.spread, projection.rightPlane + projection.spread, projection.bottomPlane, projection.topPlane, projection.nearPlane, projection.farPlane);
		}
		static glm::mat4 createOrthographic(float leftPlane, float rightPlane, float bottomPlane, float topPlane, float nearPlane, float farPlane, float spread = 0.0f)
		{
			return glm::ortho(leftPlane - spread, rightPlane + spread, bottomPlane, topPlane);
		}

		static glm::mat4 createPerspective(PerspectiveSettings projection)
		{
			return glm::perspective(glm::radians(projection.fov), projection.aspectRatio, projection.nearPlane, projection.farPlane);
		}
		static glm::mat4 createPerspective(float fov, float aspectRatio, float nearPlane, float farPlane)
		{
			return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
		}
	};
}

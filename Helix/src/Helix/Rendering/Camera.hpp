#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Helix/Scene/Transform.hpp"
#include "Helix/Rendering/Projection.hpp"

namespace hlx
{
	class Camera
	{
	public:

		Camera();
		Camera(Transform transform, glm::vec3 worldUp = glm::vec3{ 0.0f, 1.0f, 0.0f });
		~Camera() = default;

		void update();
		void updateProjections();

		Transform& getTransform();
		void setTransform(const Transform& transform);

		const glm::mat4& getViewMatrix() const;
		const glm::mat4& getProjectionMatrix() const;
		const glm::mat4 getViewProjectionMatrix() const;

		ProjectionType getProjectionType() const;
		void setProjectionType(ProjectionType type);

		OrthographicProjection& getOrthographicProjection();
		PerspectiveProjection& getPerspectiveProjection();

	private:
		Transform m_transform;

		glm::vec3 m_up;
		glm::vec3 m_forward;
		glm::vec3 m_right;

		glm::vec3 m_worldUp;

		glm::mat4 m_viewMatrix;
		glm::mat4 m_projectionMatrix;

		ProjectionType m_projectionType;
		OrthographicProjection m_orthographicProjection;
		PerspectiveProjection m_perspectiveProjection;

		bool m_hasTarget;
	};
}

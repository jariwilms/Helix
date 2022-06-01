#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Helix/Input/Input.hpp"
#include "Helix/Scene/Transform.hpp"
#include "Helix/Rendering/Projection.hpp"

namespace hlx
{
	class Camera
	{
	public:

		Camera(Transform transform = Transform{}, glm::vec3 worldUp = glm::vec3{ 0.0f, 1.0f, 0.0f }, Projection::Type projectionType = Projection::Type::Orthographic);
		~Camera() = default;

		void update();
		void updateTransform();
		void updateMatrices();

		Projection::Type getProjectionType() const;
		void setProjectionType(Projection::Type type);

		const glm::mat4& getViewMatrix() const;
		const glm::mat4& getProjectionMatrix() const;
		const glm::mat4& getViewProjectionMatrix() const;

		Projection::OrthographicSettings getOrthographicProjectionSettings() const;
		void setOrthographicSettings(const Projection::OrthographicSettings& settings);

		Projection::PerspectiveSettings getPerspectiveProjectionSettings() const;
		void setPerspectiveSettings(const Projection::PerspectiveSettings& settings);

		Transform transform;
	private:

		glm::vec3 m_up;
		glm::vec3 m_forward;
		glm::vec3 m_right;

		glm::vec3 m_worldUp;

		glm::mat4 m_viewMatrix;
		glm::mat4 m_projectionMatrix;
		glm::mat4 m_viewProjectionMatrix;

		Projection::Type m_projectionType;
		Projection::OrthographicSettings m_orthographicProjectionSettings;
		Projection::PerspectiveSettings m_perspectiveProjectionSettings;

		bool m_isLocked;
		bool m_hasTarget;
	};
}

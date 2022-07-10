#pragma once

#include "stdafx.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Helix/Library/Transform.hpp"
#include "Helix/Input/Input.hpp"
#include "Helix/Scene/Camera/Projection.hpp"

namespace hlx
{
	class Camera
	{
	public:
		enum class Mode
		{
			Free, 
			Target, 
			Locked
		};

		Camera(Transform transform = Transform{}, glm::vec3 worldUp = glm::vec3{ 0.0f, 1.0f, 0.0f }, Projection::Type projectionType = Projection::Type::Orthographic);
		~Camera() = default;

		void update(DeltaTime deltaTime);

		inline Mode getMode() { return m_mode; }
		inline void setMode(Mode mode) { m_mode = mode; }

		inline Transform& getTransform() { return m_transform; }
		inline void setTransform(Transform transform) { m_transform = transform; }

		void setScreenDimensions(glm::vec2 dimensions);

		inline Projection::Type getProjectionType() const { return m_projectionType; }
		void setProjectionType(Projection::Type type);
		void updateProjection();

		inline const glm::mat4& getViewMatrix() const { return m_viewMatrix; }
		inline const glm::mat4& getProjectionMatrix() const { return m_projectionMatrix; }

		inline Projection::OrthographicSettings getOrthographicProjectionSettings() const { return m_orthographicProjectionSettings; }
		inline void setOrthographicProjectionSettings(const Projection::OrthographicSettings& settings) { m_orthographicProjectionSettings = settings; }

		inline Projection::PerspectiveSettings getPerspectiveProjectionSettings() const { return m_perspectiveProjectionSettings; }
		inline void setPerspectiveProjectionSettings(const Projection::PerspectiveSettings& settings) { m_perspectiveProjectionSettings = settings; }

	private:
		Mode m_mode;
		Transform m_transform;

		glm::vec3 m_forward;
		glm::vec3 m_right;
		glm::vec3 m_up;
		
		glm::vec3 m_worldUp;

		glm::mat4 m_viewMatrix;
		glm::mat4 m_projectionMatrix;

		Projection::Type m_projectionType;
		Projection::OrthographicSettings m_orthographicProjectionSettings;
		Projection::PerspectiveSettings m_perspectiveProjectionSettings;

		glm::vec3 m_targetPosition;

		float m_speedMultiplier;

		bool m_isLocked;
		bool m_hasTarget;
	};
}

#pragma once

#include "stdafx.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Helix/Core/Transform.hpp"
#include "Helix/Input/Input.hpp"
#include "Helix/Scene/Camera/Projection.hpp"

namespace hlx
{
	class Camera
	{
	public:
		//REMOVE//
		friend class Material;
		//######//

		enum class Mode
		{
			Free, 
			Target, 
			Locked
		};

		Camera(Transform transform = Transform{}, glm::vec3 worldUp = glm::vec3{ 0.0f, 1.0f, 0.0f }, Projection::Type projectionType = Projection::Type::Orthographic);
		~Camera() = default;

		void update(DeltaTime deltaTime);

		Mode getMode();
		void setMode(Mode mode);

		Projection::Type getProjectionType() const;
		void setProjectionType(Projection::Type type);

		const glm::mat4& getViewMatrix() const;
		const glm::mat4& getProjectionMatrix() const;

		void setScreenDimensions(glm::vec2 dimensions);

		Projection::OrthographicSettings getOrthographicProjectionSettings() const;
		void setOrthographicProjectionSettings(const Projection::OrthographicSettings& settings);

		Projection::PerspectiveSettings getPerspectiveProjectionSettings() const;
		void setPerspectiveProjectionSettings(const Projection::PerspectiveSettings& settings);

		Transform transform;

	private:
		Mode m_mode;

		glm::vec3 m_up;
		glm::vec3 m_forward;
		glm::vec3 m_right;

		glm::vec3 m_worldUp;

		glm::mat4 m_viewMatrix;
		glm::mat4 m_projectionMatrix;

		Projection::Type m_projectionType;
		Projection::OrthographicSettings m_orthographicProjectionSettings;
		Projection::PerspectiveSettings m_perspectiveProjectionSettings;

		glm::vec3 m_targetPosition;

		bool m_isLocked;
		bool m_hasTarget;
	};
}

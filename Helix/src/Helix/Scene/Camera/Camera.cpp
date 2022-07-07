#include "stdafx.hpp"
#include "Camera.hpp"

#include "Helix/Core/Application.hpp"

namespace hlx
{
	Camera::Camera(Transform transform, glm::vec3 worldUp, Projection::Type projectionType)
		: m_mode{ Mode::Free }, m_transform{ transform }, m_worldUp{ worldUp }, m_speedMultiplier{ 10.0f }, m_isLocked{}, m_hasTarget{}
	{
		setProjectionType(projectionType);

		auto& dims = Application::getInstance().getWindow().getProperties().dimensions;
		setScreenDimensions(dims);
	}

	void Camera::update(DeltaTime deltaTime)
	{
		if (getMode() == Mode::Locked)
			return;

		float dt = deltaTime;
		if (Input::isKeyPressed(Key::LeftShift)) dt *= m_speedMultiplier;

		if (Input::isKeyPressed(Key::W)) m_transform.position += m_forward * dt;
		if (Input::isKeyPressed(Key::A)) m_transform.position -= glm::normalize(glm::cross(m_forward, m_up)) * dt;
		if (Input::isKeyPressed(Key::S)) m_transform.position -= m_forward * dt;
		if (Input::isKeyPressed(Key::D)) m_transform.position += glm::normalize(glm::cross(m_forward, m_up)) * dt;
		if (Input::isKeyPressed(Key::Space)) m_transform.position += m_up * dt;
		if (Input::isKeyPressed(Key::LeftControl)) m_transform.position -= m_up * dt;

		if (Input::isButtonPressed(Button::ButtonRight) && Input::isMovingCursor())
		{
			auto& cursor = Input::getRelativeCursorPosition();
			
			m_transform.rotation.x += cursor.x * deltaTime * 30;
			m_transform.rotation.y -= cursor.y * deltaTime * 30;

			m_transform.rotation.y = std::clamp(m_transform.rotation.y, -89.0f, 89.0f);
		}
		
		if (Input::isScrolling())
		{
			auto& scroll = Input::getScrollDirection();

			auto& spread = m_orthographicProjectionSettings.spread;
			auto& fov = m_perspectiveProjectionSettings.fov;
			
			if (scroll.y)
			{
				spread += scroll.y * deltaTime * m_speedMultiplier;
				spread = std::clamp(spread, -1.0f, 1.0f);

				fov -= scroll.y * deltaTime * m_speedMultiplier;
				fov = std::clamp(fov, 1.0f, 45.0f);
				
				updateProjection();
			}
		}

		//We want the default rotation vector(0.0f, 0.0f, 0.0f) to face into the screen towards the negative z-axis
		m_forward.x = (float)( glm::sin(glm::radians(m_transform.rotation.x)) * glm::cos(glm::radians(m_transform.rotation.y)));
		m_forward.y = (float)( glm::sin(glm::radians(m_transform.rotation.y)));
		m_forward.z = (float)(-glm::cos(glm::radians(m_transform.rotation.x)) * glm::cos(glm::radians(m_transform.rotation.y)));
		m_forward = glm::normalize(m_forward);

		m_right = glm::normalize(glm::cross(m_forward, m_worldUp));
		m_up = glm::normalize(glm::cross(m_right, m_forward));



		switch (getMode())
		{
			case Mode::Free:
				m_viewMatrix = glm::lookAt(m_transform.position, m_transform.position + m_forward, m_up);
				break;
			case Mode::Target:
				m_viewMatrix = glm::lookAt(m_transform.position, m_targetPosition, m_up);
				break;

			default:
				break;
		}
	}

	void Camera::setScreenDimensions(glm::vec2 dimensions)
	{
		float aspectRatio = dimensions.x / dimensions.y;

		m_orthographicProjectionSettings.leftPlane = -aspectRatio;
		m_orthographicProjectionSettings.rightPlane = aspectRatio;
		m_perspectiveProjectionSettings.aspectRatio = aspectRatio;

		setProjectionType(getProjectionType());
	}

	void Camera::setProjectionType(Projection::Type type)
	{
		m_projectionType = type;
		updateProjection();
	}

	void Camera::updateProjection()
	{
		switch (m_projectionType)
		{
			case Projection::Type::Orthographic:
				m_projectionMatrix = Projection::createOrthographic(m_orthographicProjectionSettings);
				break;
			case Projection::Type::Perspective:
				m_projectionMatrix = Projection::createPerspective(m_perspectiveProjectionSettings);
				break;
		}
	}
}

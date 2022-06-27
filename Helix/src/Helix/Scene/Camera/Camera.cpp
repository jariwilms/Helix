#include "stdafx.hpp"
#include "Camera.hpp"

#include "Helix/Core/Application.hpp"

namespace hlx
{
	Camera::Camera(Transform transform, glm::vec3 worldUp, Projection::Type projectionType)
		: transform{ transform }, m_worldUp{ worldUp }, m_isLocked{}, m_hasTarget{}, m_mode{ Mode::Free }
	{
		this->transform.rotation.y -= 90.0f;

		setProjectionType(projectionType);

		auto& dims = Application::getInstance().getWindow().getProperties().dimensions;
		setScreenDimensions(dims);
	}

	void Camera::update(DeltaTime deltaTime)
	{
		if (getMode() == Mode::Locked)
			return;

		float dt = deltaTime;
		if (Input::isKeyPressed(Key::LeftShift)) dt *= 10.0f;

		if (Input::isKeyPressed(Key::W)) transform.position += m_forward * dt;
		if (Input::isKeyPressed(Key::A)) transform.position -= glm::normalize(glm::cross(m_forward, m_up)) * dt;
		if (Input::isKeyPressed(Key::S)) transform.position -= m_forward * dt;
		if (Input::isKeyPressed(Key::D)) transform.position += glm::normalize(glm::cross(m_forward, m_up)) * dt;
		if (Input::isKeyPressed(Key::Space)) transform.position += m_up * dt;
		if (Input::isKeyPressed(Key::LeftControl)) transform.position -= m_up * dt;

		if (Input::isButtonPressed(Button::ButtonRight) && Input::isMovingCursor())
		{
			auto& cursor = Input::getRelativeCursorPosition();
			transform.rotation.x += -cursor.y * deltaTime * 30;
			transform.rotation.y += cursor.x * deltaTime * 30;
		}



		m_forward.x = (float)(glm::cos(glm::radians(transform.rotation.y)) * glm::cos(glm::radians(transform.rotation.x)));
		m_forward.y = (float)(glm::sin(glm::radians(transform.rotation.x)));
		m_forward.z = (float)(glm::sin(glm::radians(transform.rotation.y)) * glm::cos(glm::radians(transform.rotation.x)));
		m_forward = glm::normalize(m_forward);

		m_right = glm::normalize(glm::cross(m_forward, m_worldUp));
		m_up = glm::normalize(glm::cross(m_right, m_forward));



		switch (getMode())
		{
			case Mode::Free:
				m_viewMatrix = glm::lookAt(transform.position, transform.position + m_forward, m_up);
				break;
			case Mode::Target:
				m_viewMatrix = glm::lookAt(transform.position, m_targetPosition, m_up);
				break;

			default:
				break;
		}
	}

	hlx::Camera::Mode Camera::getMode()
	{
		return m_mode;
	}
	void Camera::setMode(Mode mode)
	{
		m_mode = mode;
	}

	Projection::Type Camera::getProjectionType() const
	{
		return m_projectionType;
	}
	void Camera::setProjectionType(Projection::Type type)
	{
		m_projectionType = type;

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

	const glm::mat4& Camera::getViewMatrix() const
	{
		return m_viewMatrix;
	}
	const glm::mat4& Camera::getProjectionMatrix() const
	{
		return m_projectionMatrix;
	}

	void Camera::setScreenDimensions(glm::vec2 dimensions)
	{
		float aspectRatio = dimensions.x / dimensions.y;

		m_orthographicProjectionSettings.leftPlane = -aspectRatio;
		m_orthographicProjectionSettings.rightPlane = aspectRatio;
		m_perspectiveProjectionSettings.aspectRatio = aspectRatio;

		setProjectionType(getProjectionType());
	}

	Projection::OrthographicSettings Camera::getOrthographicProjectionSettings() const
	{
		return m_orthographicProjectionSettings;
	}
	void Camera::setOrthographicSettings(const Projection::OrthographicSettings& settings)
	{
		m_orthographicProjectionSettings = settings;
	}

	Projection::PerspectiveSettings Camera::getPerspectiveProjectionSettings() const
	{
		return m_perspectiveProjectionSettings;
	}
	void Camera::setPerspectiveSettings(const Projection::PerspectiveSettings& settings)
	{
		m_perspectiveProjectionSettings = settings;
	}
}

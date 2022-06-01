#include "stdafx.hpp"
#include "Camera.hpp"

namespace hlx
{
	Camera::Camera(Transform transform, glm::vec3 worldUp, Projection::Type projectionType)
		: transform{ transform }, m_worldUp{ worldUp }, m_projectionType{ projectionType }, m_isLocked{}, m_hasTarget{}
	{
		this->transform.rotation.y -= 90.0f;
		update();
	}

	void Camera::update()
	{
		m_forward.x = (float)(glm::cos(glm::radians(transform.rotation.y)) * glm::cos(glm::radians(transform.rotation.x)));
		m_forward.y = (float)(glm::sin(glm::radians(transform.rotation.x)));
		m_forward.z = (float)(glm::sin(glm::radians(transform.rotation.y)) * glm::cos(glm::radians(transform.rotation.x)));
		m_forward = glm::normalize(m_forward);

		m_right = glm::normalize(glm::cross(m_forward, m_worldUp));
		m_up = glm::normalize(glm::cross(m_right, m_forward));

		updateTransform();
		updateMatrices();
	}
	void Camera::updateTransform()
	{
		if (Input::isKeyPressed(Key::W))
			transform.position.z -= 0.1f;

		if (Input::isKeyPressed(Key::A))
			transform.position.x -= 0.1f;

		if (Input::isKeyPressed(Key::S))
			transform.position.z += 0.1f;

		if (Input::isKeyPressed(Key::D))
			transform.position.x += 0.1f;

		//auto& rotation = Input::getRelativeCursorPosition();
		//transform.rotation.y += rotation.x / 10.0f; //TODO: fix met timestep
		//transform.rotation.x += rotation.y;
	}
	void Camera::updateMatrices()
	{
		m_viewMatrix = glm::lookAt(transform.position, transform.position + m_forward, m_up);

		switch (m_projectionType)
		{
			case Projection::Type::Orthographic:
				m_projectionMatrix = Projection::createOrthographic(m_orthographicProjectionSettings);
				break;
			case Projection::Type::Perspective:
				m_projectionMatrix = Projection::createPerspective(m_perspectiveProjectionSettings);
				break;
		}

		m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
	}

	Projection::Type Camera::getProjectionType() const
	{
		return m_projectionType;
	}
	void Camera::setProjectionType(Projection::Type type)
	{
		m_projectionType = type;
		updateMatrices();
	}

	const glm::mat4& Camera::getViewMatrix() const
	{
		return m_viewMatrix;
	}
	const glm::mat4& Camera::getProjectionMatrix() const
	{
		return m_projectionMatrix;
	}
	const glm::mat4& Camera::getViewProjectionMatrix() const
	{
		return m_viewProjectionMatrix;
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

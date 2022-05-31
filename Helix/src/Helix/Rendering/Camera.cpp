#include "stdafx.hpp"
#include "Camera.hpp"

namespace hlx
{
	Camera::Camera()
		: m_up{}, m_forward{}, m_right{}, m_worldUp{ 0.0f, 1.0f, 0.0f }, m_hasTarget{} 
	{
		update();
	}

	Camera::Camera(Transform transform, glm::vec3 worldUp)
		: m_transform{ transform }, m_worldUp{ worldUp }
	{
		m_transform.rotation.y += glm::radians(90.0f);
		Camera();
	}

	void Camera::update()
	{
		m_forward.x = (float)(glm::cos(m_transform.rotation.y) * glm::cos(m_transform.rotation.x));
		m_forward.y = (float)(glm::sin(m_transform.rotation.x));
		m_forward.z = (float)(glm::sin(m_transform.rotation.y) * glm::cos(m_transform.rotation.x));
		m_forward = glm::normalize(m_forward);

		m_right = glm::normalize(glm::cross(m_forward, m_worldUp));
		m_up = glm::normalize(glm::cross(m_right, m_up));
	}

	void Camera::updateProjections()
	{
		setProjectionType(m_projectionType);
	}

	const glm::mat4& Camera::getViewMatrix() const
	{
		return m_viewMatrix;
	}

	const glm::mat4& Camera::getProjectionMatrix() const
	{
		return m_projectionMatrix;
	}

	const glm::mat4 Camera::getViewProjectionMatrix() const
	{
		return getProjectionMatrix() * getViewMatrix();
	}

	Transform& Camera::getTransform()
	{
		return m_transform;
	}

	void Camera::setTransform(const Transform& transform)
	{
		m_transform = transform;
	}

	ProjectionType Camera::getProjectionType() const
	{
		return m_projectionType;
	}

	void Camera::setProjectionType(ProjectionType type)
	{
		m_projectionType = type;

		switch (m_projectionType)
		{
			case ProjectionType::Orthographic:
				m_viewMatrix = OrthographicProjection::create(m_orthographicProjection);
				break;
			case ProjectionType::Perspective:
				m_projectionMatrix = PerspectiveProjection::create(m_perspectiveProjection);
				break;
		}
	}

	OrthographicProjection& Camera::getOrthographicProjection()
	{
		return m_orthographicProjection;
	}

	PerspectiveProjection& Camera::getPerspectiveProjection()
	{
		return m_perspectiveProjection;
	}

}

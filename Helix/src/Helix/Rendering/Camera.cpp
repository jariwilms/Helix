#include "stdafx.hpp"
#include "Camera.hpp"

namespace hlx
{
	Camera::Axes::Axes()
		: yaw{}, pitch{}, roll{} {}

	Camera::Axes::Axes(double yaw, double pitch, double roll)
		: yaw{ yaw }, pitch{ pitch }, roll{ roll } {}

	Camera::Camera()
		: m_position{}, m_up{}, m_forward{}, m_right{}, m_worldUp{ 0.0f, 1.0f, 0.0f } {}

	Camera::Camera(glm::vec3 position, glm::vec3 up, Axes axes)
		: m_position{ position }, m_worldUp{ up } 
	{
		Camera();
	}

	void Camera::update()
	{
		m_forward.x = (float)(glm::cos(m_axes.yaw) * glm::cos(m_axes.pitch));
		m_forward.y = (float)(glm::sin(m_axes.pitch));
		m_forward.z = (float)(glm::sin(m_axes.yaw) * glm::cos(m_axes.pitch));
		m_forward = glm::normalize(m_forward);

		m_right = glm::normalize(glm::cross(m_forward, m_worldUp));
		m_up = glm::normalize(glm::cross(m_right, m_up));
	}

	glm::mat4 Camera::getViewMatrix() const
	{
		return glm::lookAt(m_position, m_position + m_forward, m_up);
	}

	glm::vec3 Camera::getPosition() const
	{
		return m_position;
	}

	hlx::Camera::Axes Camera::getAxes() const
	{
		return m_axes;
	}
}

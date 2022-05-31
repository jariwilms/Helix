#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace hlx
{
	class Camera
	{
	public:
		struct Axes
		{
			Axes();
			Axes(double yaw, double pitch, double roll);

			double yaw;
			double pitch;
			double roll;
		};

		Camera();
		Camera(glm::vec3 position, glm::vec3 up = glm::vec3{ 0.0f, 1.0f, 0.0f }, Axes axes = Axes{});
		~Camera() = default;

		void update();

		glm::mat4 getViewMatrix() const;

		glm::vec3 getPosition() const;
		Axes getAxes() const;

	private:
		glm::vec3 m_position;

		glm::vec3 m_up;
		glm::vec3 m_forward;
		glm::vec3 m_right;

		glm::vec3 m_worldUp;

		Axes m_axes;
	};
}

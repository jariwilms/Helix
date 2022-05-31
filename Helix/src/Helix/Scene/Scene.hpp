#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Camera.hpp"

namespace hlx
{
	class Scene
	{
	public:
		Scene();
		~Scene();

		const Camera& getCamera();

	private:
		Camera m_camera;
	};
}

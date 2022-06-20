#pragma once

#include "Helix/Rendering/Mesh/Mesh.hpp"

namespace hlx
{
	class OpenGLMesh : public Mesh
	{
	public:
		OpenGLMesh();
		~OpenGLMesh() override;
	};
}

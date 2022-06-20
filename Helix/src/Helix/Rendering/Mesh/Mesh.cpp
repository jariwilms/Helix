#include "stdafx.hpp"
#include "Mesh.hpp"

#include "Helix/Rendering/API/OpenGL/Mesh/OpenGLMesh.hpp"

namespace hlx
{
	std::shared_ptr<Mesh> Mesh::create()
	{
		return std::make_shared<OpenGLMesh>();
	}
}

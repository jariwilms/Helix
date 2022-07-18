#include "stdafx.hpp"
#include "VertexArray.hpp"

#include "Helix/Rendering/API/OpenGL/Object/OpenGLVertexArray.hpp"

namespace hlx
{
	template <typename T>
	std::shared_ptr<VertexArray<T>> VertexArray<T>::create()
	{
		return std::make_shared<OpenGLVertexArray<T>>();
	}

	template class VertexArray<float>;
	template class VertexArray<Vertex>;
	template class VertexArray<MeshVertex>;
}

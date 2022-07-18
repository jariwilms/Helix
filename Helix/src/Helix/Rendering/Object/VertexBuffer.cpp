#include "stdafx.hpp"
#include "VertexBuffer.hpp"

#include "Helix/Rendering/API/OpenGL/Object/OpenGLVertexBuffer.hpp"

namespace hlx
{
	template <typename T>
	std::shared_ptr<VertexBuffer<T>> VertexBuffer<T>::create(unsigned int count, const float* data)
	{
		return std::make_shared<OpenGLVertexBuffer<T>>(count, data);
	}
	
	template class VertexBuffer<float>;
	template class VertexBuffer<Vertex>;
	template class VertexBuffer<MeshVertex>;
}

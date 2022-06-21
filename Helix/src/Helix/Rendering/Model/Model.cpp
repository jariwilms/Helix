#include "stdafx.hpp"
#include "Model.hpp"

#include "Helix/Rendering/API/OpenGL/Model/OpenGLModel.hpp"

namespace hlx
{
	std::shared_ptr<Model> Model::create(std::filesystem::path path)
	{
		return IO::load<Model>(path);
	}

	std::shared_ptr<Model> Model::create()
	{
		return std::make_shared<OpenGLModel>();
	}
}

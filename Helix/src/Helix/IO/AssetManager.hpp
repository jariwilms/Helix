#pragma once

#include "Helix/IO/Format/File.hpp"

namespace hlx
{
	class AssetManager
	{
	private:
		inline static std::unordered_map<std::filesystem::path, std::shared_ptr<File>> m_files;
		inline static std::unordered_map<std::filesystem::path, std::shared_ptr<Texture>> m_textures;
		inline static std::unordered_map<std::filesystem::path, std::shared_ptr<Model>> m_models;
	};
}

#pragma once

#include "Helix/IO/Format/File.hpp"

namespace hlx
{
	class AssetManager
	{
	private:
		static inline std::unordered_map<std::filesystem::path, std::shared_ptr<File>> m_files;
		static inline std::unordered_map<std::filesystem::path, std::shared_ptr<Texture>> m_textures;
		static inline std::unordered_map<std::filesystem::path, std::shared_ptr<Model>> m_models;
	};
}

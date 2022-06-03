#pragma once

#include "stdafx.hpp"

#pragma warning(disable: 26819 6262 26451)
#include "stb/stb_image.h"
#pragma warning(default: 26819 6262 26451)

#include "Helix/Rendering/Texture.hpp"

namespace hlx
{
	class IO
	{
	public:
		static void init();

		static bool checkFileExists(const std::filesystem::path& path);
		static bool checkDirectoryExists(const std::filesystem::path& path);

		static const std::filesystem::path& getRoot();
		static void setRoot(const std::filesystem::path& root);
		static void appendRoot(const std::filesystem::path& directory);

		static std::filesystem::path getWorkingDirectory();
		static std::filesystem::path getCompoundPath(const std::filesystem::path& path);

		template<typename T>
		static std::shared_ptr<T> load(const std::filesystem::path& path)
		{
			HLX_CORE_ASSERT(false, "Invalid file format");
		}
		template<> static std::shared_ptr<std::string> load<std::string>(const std::filesystem::path& path)
		{
			if (m_strings.find(path) != m_strings.end())
				return m_strings[path];

			std::filesystem::path destination = getCompoundPath(path);
			if (!checkFileExists(destination))
				logError(path);



			std::ifstream file(destination);
			auto result = std::make_shared<std::string>();
			*result = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

			m_strings.insert(std::make_pair(path, result));
			file.close();

			return m_strings[path];
		}
		template<> static std::shared_ptr<Texture> load<Texture>(const std::filesystem::path& path)
		{
			if (m_textures.find(path) != m_textures.end())
				return m_textures[path];

			std::filesystem::path destination = getCompoundPath(path);
			if (!checkFileExists(destination))
				logError(path);



			int width, height, channels;
			unsigned char* data;

			stbi_set_flip_vertically_on_load(true);
			data = stbi_load(getCompoundPath(path).generic_string().c_str(), &width, &height, &channels, 0);

			auto texture = Texture::create(width, height, channels, data);
			m_textures.insert(std::make_pair(path, texture));

			return texture;
		}

	private:
		static void logError(std::filesystem::path path);

		static std::filesystem::path m_root;

		static std::unordered_map<std::filesystem::path, std::shared_ptr<std::string>> m_strings;
		static std::unordered_map<std::filesystem::path, std::shared_ptr<Texture>> m_textures;
	};
}

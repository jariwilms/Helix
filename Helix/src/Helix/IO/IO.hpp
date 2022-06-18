#pragma once

#include "stdafx.hpp"

#pragma warning(disable: 26819 6262 26451)
#include "stb/stb_image.h"
#pragma warning(default: 26819 6262 26451)

#include "Helix/Rendering/Texture/Texture.hpp"

namespace hlx
{
	class IO
	{
	public:
		static void init()
		{
			m_root = std::filesystem::current_path().parent_path().lexically_normal();
			HLX_CORE_INFO("HLX::IO::INIT");
			HLX_CORE_INFO("Setting root path to {0}", m_root.string().c_str());
		}

		inline static bool checkFileExists(const std::filesystem::path& path) { return std::filesystem::exists(path);  }
		inline static bool checkDirectoryExists(const std::filesystem::path& path) { return std::filesystem::exists(path); }

		inline static const std::filesystem::path& getRoot() { return m_root; }
		inline static void setRoot(const std::filesystem::path& root) { m_root = root; }

		inline static std::filesystem::path getCurrentWorkingDirectory() { return std::filesystem::current_path(); }
		inline static std::filesystem::path getCoalescedPath(std::filesystem::path path = "")
		{
			std::filesystem::path coalesced = m_root;
			std::for_each(m_subdirectories.begin(), m_subdirectories.end(), [&](const std::filesystem::path& _) { coalesced /= _; });

			return (coalesced / path).lexically_normal();
		}

		template<typename T>
		inline static std::shared_ptr<T> load(const std::filesystem::path& path)
		{
			HLX_CORE_ASSERT(false, "Invalid file format");
		}
		template<> inline static std::shared_ptr<std::string> load<std::string>(const std::filesystem::path& path)
		{
			auto fullPath = getCoalescedPath(path);

			if (!checkFileExists(fullPath)) logError(fullPath);
			if (m_textFiles.find(fullPath) != m_textFiles.end()) return m_textFiles[fullPath];



			std::ifstream file(fullPath);
			auto result = std::make_shared<std::string>();
			*result = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

			m_textFiles.insert(std::make_pair(fullPath, result));
			file.close();

			return m_textFiles[fullPath];
		}
		template<> inline static std::shared_ptr<Texture> load<Texture>(const std::filesystem::path& path)
		{
			auto fullPath = getCoalescedPath(path);

			if (!checkFileExists(fullPath)) logError(fullPath);
			if (m_textures.find(fullPath) != m_textures.end()) return m_textures[fullPath];



			int width, height, channels;
			unsigned char* data;

			stbi_set_flip_vertically_on_load(true);
			data = stbi_load(fullPath.string().c_str(), &width, &height, &channels, 0);

			auto texture = Texture::create(width, height, channels, data);
			m_textures.insert(std::make_pair(fullPath, texture));

			return texture;
		}

		class Affix
		{
		public:
			Affix(const std::filesystem::path relativePath) 
			{ 
				HLX_CORE_INFO("Appended \"{0}\" to current path", relativePath.string().c_str());
				IO::m_subdirectories.push_back(relativePath); }
			~Affix()
			{ 
				auto& relativePath = m_subdirectories.at(m_subdirectories.size() - 1);
				HLX_CORE_INFO("Detached \"{0}\" from current path", relativePath.string().c_str());
				IO::m_subdirectories.pop_back(); }
		};

	private:
		inline static void logError(std::filesystem::path path)
		{
			const std::string filename = path.filename().string();
			const std::string parent = path.remove_filename().generic_string();
			HLX_CORE_WARNING("File \"{0}\" was not found at location \"{1}\"", filename, parent);
		}

		inline static std::filesystem::path m_root;
		inline static std::vector<std::filesystem::path> m_subdirectories;

		inline static std::unordered_map<std::filesystem::path, std::shared_ptr<std::string>> m_textFiles;
		inline static std::unordered_map<std::filesystem::path, std::shared_ptr<Texture>> m_textures;
	};
}

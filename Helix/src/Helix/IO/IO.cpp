#include "stdafx.hpp"
#include "IO.hpp"

namespace hlx
{
	void IO::init()
	{
		m_root = std::filesystem::current_path();
		HLX_CORE_INFO("HLX::IO::INIT");
	}

	bool IO::checkFileExists(const std::filesystem::path& path)
	{
		return std::filesystem::exists(path);
	}
	bool IO::checkDirectoryExists(const std::filesystem::path& path)
	{
		return std::filesystem::exists(path);
	}

	const std::filesystem::path& IO::getRoot()
	{
		return m_root;
	}
	void IO::setRoot(const std::filesystem::path& root)
	{
		m_root = root;
	}
	void IO::appendRoot(const std::filesystem::path& directory)
	{
		m_root.append(directory.native());
	}

	std::filesystem::path IO::getWorkingDirectory()
	{
		return std::filesystem::current_path();
	}
	std::filesystem::path IO::getCompoundPath(const std::filesystem::path& path)
	{
		return m_root / path;
	}

	void IO::logError(std::filesystem::path path)
	{
		const std::string filename = path.filename().string();
		const std::string parent = path.remove_filename().generic_string();
		HLX_CORE_WARNING("File \"{0}\" was not found at location \"{1}\"", filename, parent);
	}

	std::filesystem::path IO::m_root;

	std::unordered_map<std::filesystem::path, std::shared_ptr<std::string>> IO::m_strings;
	std::unordered_map<std::filesystem::path, std::shared_ptr<Image>> IO::m_images;
	std::unordered_map<std::filesystem::path, std::shared_ptr<Texture>> IO::m_textures;
}

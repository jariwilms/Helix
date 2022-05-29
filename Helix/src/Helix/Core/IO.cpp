#include "stdafx.hpp"
#include "IO.hpp"

namespace hlx
{
	std::filesystem::path IO::m_root;

	void IO::init()
	{
		m_root = std::filesystem::current_path();
		HLX_CORE_INFO("HLX::IO::INIT");
	}

	bool IO::checkFileExists(const std::filesystem::path path)
	{
		return std::filesystem::exists(path);
	}

	const std::filesystem::path IO::getCurrentRootDirectory()
	{
		return m_root;
	}
	const std::filesystem::path IO::getCurrentWorkingDirectory()
	{
		return std::filesystem::current_path();
	}
	const std::filesystem::path IO::getCompoundPath(const std::filesystem::path& path)
	{
		return m_root / path;
	}

	void IO::setRootDirectory(const std::filesystem::path& root)
	{
		m_root = root;
	}
	void IO::appendRootDirectory(const std::filesystem::path& directory)
	{
		m_root.append(directory.native());
	}

	const std::string IO::readFileToString(const std::filesystem::path& path)
	{
		std::filesystem::path destination = getCompoundPath(path);
		bool exists = checkFileExists(destination);

		if (!exists)
		{
			const std::string filename = destination.filename().string();
			const std::string path = destination.remove_filename().generic_string();
			//HLX_CORE_WARNING("File \"{0}\" was not found at location \"{1}\"", filename, path);

			return std::string();
		}

		//HLX_CORE_INFO("Reading file at location: \"{0}\"", path);
		std::ifstream file(destination);

		return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	}
}

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

	bool IO::fileExists(const std::filesystem::path path)
	{
		return std::filesystem::exists(path);
	}

	const std::filesystem::path IO::getCurrentRoot()
	{
		return m_root;
	}
	const std::filesystem::path IO::getCurrentWorkingDirectory()
	{
		return std::filesystem::current_path();
	}
	const std::filesystem::path IO::getCompoundPath(const std::string& path)
	{
		return m_root.append(path);
	}

	void IO::setRootDirectory(const std::filesystem::path& root)
	{
		m_root = root;
	}
	void IO::appendToRootDirectory(const std::string& directory)
	{
		m_root = m_root.append(directory);
	}

	const std::string IO::readFileToString(const std::string& path)
	{
		auto destination = getCompoundPath(path);

		if (!fileExists(destination))
		{
			const std::string filename = destination.filename().string();
			const std::string path = destination.remove_filename().generic_string();
			HLX_CORE_WARNING("File \"{0}\" was not found at location \"{1}\"", filename, path);

			return std::string();
		}

		HLX_CORE_INFO("Reading file at location: \"{0}\"", path);
		std::ifstream file(destination);
		return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	}
}

#pragma once

#include "stdafx.hpp"

namespace hlx
{
	class IO
	{
	public:
		static void init();

		static bool checkFileExists(const std::filesystem::path path);

		static const std::filesystem::path getCurrentRootDirectory();
		static const std::filesystem::path getCurrentWorkingDirectory();
		static const std::filesystem::path getCompoundPath(const std::filesystem::path& path);

		static void setRootDirectory(const std::filesystem::path& directory);
		static void appendRootDirectory(const std::filesystem::path& directory);

		static const std::string readFileToString(const std::filesystem::path& path);

	private:
		static std::filesystem::path m_root;
	};
}

#pragma once

#include "stdafx.hpp"

namespace hlx
{
	class IO
	{
	public:
		static void init();

		static bool fileExists(const std::filesystem::path path);

		static const std::filesystem::path getCurrentRoot();
		static const std::filesystem::path getCurrentWorkingDirectory();
		static const std::filesystem::path getCompoundPath(const std::string& path);

		static void setRootDirectory(const std::filesystem::path& directory);
		static void appendToRootDirectory(const std::string& directory);

		static const std::string readFileToString(const std::string& path);

	private:
		static std::filesystem::path m_root;
	};
}

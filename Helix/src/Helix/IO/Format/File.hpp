#pragma once

#include "stdafx.hpp"

class File
{
public:
	File() = default;
	File(std::string content) : m_content{ content } {}
	File(const std::string& content) : m_content{ content } {}
	File(std::string&& content) : m_content{ content } {}

	File& operator=(std::string& other) { m_content = other; }
	File& operator=(std::string&& other) { m_content = std::move(other); return *this; }
	operator std::string() { return m_content; }

private:
	std::string m_content;
};
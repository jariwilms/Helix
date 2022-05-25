#include "stdafx.hpp"
#include "Window.hpp"

hlx::WindowSettings::WindowSettings()
{
	this->title = "";
	this->width = 0;
	this->height = 0;
}

hlx::WindowSettings::WindowSettings(const char* title, unsigned int width, unsigned int height)
	: title{ title }, width{ width }, height{ height }
{

}


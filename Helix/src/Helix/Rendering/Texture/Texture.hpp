#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "stb/stb_image.h"

#include "Helix/Rendering/Object/BufferObject.hpp"
#include "Helix/Rendering/API/OpenGL/OpenGLRenderState.hpp"

namespace hlx
{
	class Texture : public BufferObject
	{
	public:
		virtual ~Texture() = default;

		static std::shared_ptr<Texture> create(const std::filesystem::path& path);
		static std::shared_ptr<Texture> create(glm::uvec2 dimensions, unsigned int channels, unsigned char* data = nullptr);

		virtual void bindUnit(unsigned int index) const = 0;

		inline glm::uvec2 getDimensions() const { return m_dimensions; }
		inline unsigned int getChannels() const { return m_channels; }
		inline const unsigned char* getData() const { return m_data; }

	protected:
		Texture() : m_dimensions{}, m_channels{}, m_data{}, m_internalFormat{}, m_dataFormat{} {}

		virtual void setData(glm::uvec2 dimensions, unsigned int channels, unsigned char* data) = 0;

		glm::uvec2 m_dimensions;
		unsigned int m_channels;
		unsigned char* m_data;

		int m_internalFormat;
		unsigned int m_dataFormat;
	};
}

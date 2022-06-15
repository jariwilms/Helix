#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "stb/stb_image.h"

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"

namespace hlx
{
	class Texture
	{
	public:
		static std::shared_ptr<Texture> create(const std::filesystem::path& path);
		static std::shared_ptr<Texture> create(unsigned int width, unsigned int height, unsigned int channels, unsigned char* data = nullptr);

		virtual ~Texture();

		virtual void bind(unsigned int index) const = 0;
		virtual void unbind() const = 0;

		inline unsigned int getId() const { return m_textureId; }
		inline unsigned int getWidth() const { return m_width; }
		inline unsigned int getHeight() const { return m_height; }
		inline unsigned int getChannels() const { return m_channels; }
		inline const unsigned char* getData() const { return m_data; }

		bool verify() const;

	protected:
		Texture(unsigned int width, unsigned int height, unsigned int channels, unsigned char* data);

		unsigned int m_textureId;

		int m_internalFormat;
		unsigned int m_dataFormat;

		unsigned int m_width;
		unsigned int m_height;
		unsigned int m_channels;

		unsigned char* m_data;

		bool m_status;
	};
}

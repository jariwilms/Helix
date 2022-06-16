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
		virtual ~Texture();

		static std::shared_ptr<Texture> create(const std::filesystem::path& path);
		static std::shared_ptr<Texture> create(unsigned int width, unsigned int height, unsigned int channels, unsigned char* data = nullptr);

		virtual void bind() const = 0;
		virtual void bindUnit(unsigned int index) const = 0;
		virtual void unbind() const = 0;

		virtual void resize(unsigned int width, unsigned int height, unsigned int channels) = 0;
		virtual void reset() = 0;

		virtual void setBufferData(unsigned int width, unsigned int height, unsigned int channels, unsigned char* data) = 0;

		inline unsigned int getId() const { return m_textureId; }
		inline unsigned int getWidth() const { return m_width; }
		inline unsigned int getHeight() const { return m_height; }
		inline unsigned int getChannels() const { return m_channels; }
		inline const unsigned char* getData() const { return m_data; }

		inline bool verify() const { return m_status; }

	protected:
		Texture();

		unsigned int m_textureId;

		unsigned int m_width;
		unsigned int m_height;
		unsigned int m_channels;
		unsigned char* m_data;

		int m_internalFormat;
		unsigned int m_dataFormat;

		bool m_status;
	};
}

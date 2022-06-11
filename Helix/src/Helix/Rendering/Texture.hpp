#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "stb/stb_image.h"

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"

namespace hlx
{
	struct TextureSettings
	{
		//enum class Parameter
		//{
		//	TEXTURE_WRAP_S,
		//	TEXTURE_WRAP_T,

		//	TEXTURE_MIN_FILTER,
		//	TEXTURE_MAG_FILTER,
		//};

		//enum Flag
		// 
		//{
		//	REPEAT,

		//	NEAREST,
		//	LINEAR
		//};

		//Flag wrapS;
		//Flag wrapT;
		//Flag minFilter;
		//Flag magFilter;
	};

	class Texture
	{
	public:
		static std::shared_ptr<Texture> create(const std::filesystem::path& path);
		static std::shared_ptr<Texture> create(unsigned int width, unsigned int height, unsigned int channels, unsigned char* data);
		static std::shared_ptr<Texture> create(unsigned int width, unsigned int height, unsigned int channels, unsigned char* data, TextureSettings settings);

		virtual ~Texture();

		virtual void bind(unsigned int index) const = 0;

		int getWidth() const;
		int getHeight() const;
		int getChannels() const;
		const unsigned char* getData() const;

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
